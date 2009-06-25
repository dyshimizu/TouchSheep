#include "TSKernel.h"
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include <pthread.h>

int select_object = 0;
CvRect selection;
int track_object = 0;
CvPoint origin;
IplImage* image = 0;
IplImage* hue = 0;
IplImage* mask = 0;
CvHistogram *hist = 0;

void handle(IplImage* img, MarkerList list){
	if(!image){
		image = cvCreateImage( cvGetSize(img), 8, 3 );
		hue = cvCreateImage( cvGetSize(img), 8, 1 );
		mask = cvCreateImage( cvGetSize(img), 8, 1 );
	}
	
	Marker *m = list;
	while(m){
		if( !img->origin ){////////////
				m->track_box.angle = -(m->track_box.angle);////////////
			}//////////////////
			cvEllipseBox( img, m->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );////////////
		m = m->next;
	}
	cvShowImage( "TouchSheep", img );
	cvCvtColor(img, image, CV_BGR2HSV);
}

void on_mouse( int event, int x, int y, int flags, void* param ){
    if( !image )
        return;

    if( image->origin )
        y = image->height - y;

    if( select_object )
    {
        selection.x = MIN(x,origin.x);
        selection.y = MIN(y,origin.y);
        selection.width = selection.x + CV_IABS(x - origin.x);
        selection.height = selection.y + CV_IABS(y - origin.y);
        
        selection.x = MAX( selection.x, 0 );
        selection.y = MAX( selection.y, 0 );
        selection.width = MIN( selection.width, image->width );
        selection.height = MIN( selection.height, image->height );
        selection.width -= selection.x;
        selection.height -= selection.y;
    }
    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = cvPoint(x,y);
        selection = cvRect(x,y,0,0);
        select_object = 1;
        break;
    case CV_EVENT_LBUTTONUP:
        select_object = 0;
        if( selection.width > 0 && selection.height > 0 ){
            track_object = -1;
            cvInRangeS( image, cvScalar(0,30,MIN(10,256),0),
                        cvScalar(180,256,MAX(10,256),0), mask );
            cvSplit( image, hue, 0, 0, 0 );
            hist = getHistogram(hue, mask, selection);
            addMarker(selection, hist);
        }
        break;
    }
}

int main(){
	cvNamedWindow( "TouchSheep", 1 );
	cvSetMouseCallback( "TouchSheep", on_mouse, 0 );
	
	//kernelLoop(0, handle);
	pthread_t threads;
	kernel_params p;
	p.thread_id = 1;
	CvCapture *cam = cvCaptureFromCAM(0);
	p.capture = cam;
	p.handle = &handle;
	p.refresh = 30;
	p.vmin = 10;
	p.vmax = 256;
	p.smin = 30;
	int rc = pthread_create(&threads, NULL, kernelThread, (void *)&p);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
  printf("Pressione uma tecla para sair\n");
  int i;
  scanf("%d",&i);
  printf("saindo\n");
  stopKernelThread();
  cvReleaseCapture( &(cam ));
  cvDestroyWindow("TouchSheep");
  pthread_exit(NULL);
	return 0;
}


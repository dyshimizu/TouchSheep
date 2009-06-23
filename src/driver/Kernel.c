//
// Kernel.c
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#include "Kernel.h"
#include <stdio.h>
#include <pthread.h>

MarkerList markerList;
int markerId;
bool stop;

void *kernelThread(void *threadarg){
	kernel_params *p;
	p = (kernel_params *)threadarg;
	kernelLoop(p->cam, p->handle);
	pthread_exit(NULL);
}

void stopKernelThread(){
	stop = true;
}

void kernelLoop(int cam, void handle(IplImage*, MarkerList), int refresh, int vmin, int vmax, int smin){
	int count = refresh;
	
	markerList = NULL;
	markerId = 0;
	stop = false;
	
	CvCapture* capture = 0;
	
	capture = cvCaptureFromCAM(cam);
	
	IplImage* hsv = NULL;
	IplImage* hue = NULL;
	IplImage* mask = NULL;
	bool alloc = true;
	while(1){
		
		IplImage* frame = NULL;
		// aparentemente no Mac OS X cvQueryFrame nao desaloca 0.02MB a cada segundo, fazendo com que
		// a memória cresça sempre... testar no Ubuntu
		frame = cvQueryFrame( capture );
		if( !frame ){
			// erro ao capturar o frame
			return;
		}
		
		if(alloc){
			// aloca memória para as imagens
			hsv = cvCreateImage( cvGetSize(frame), 8, 3 );
			hue = cvCreateImage( cvGetSize(frame), 8, 1 );
			mask = cvCreateImage( cvGetSize(frame), 8, 1 );
			alloc = false;
		}
		
		// converte o frame para hsv
		cvCvtColor( frame, hsv, CV_BGR2HSV );
		
		// cria máscara
		cvInRangeS( hsv, cvScalar(0, smin, MIN(vmin, vmax), 0), cvScalar( 180, 256, MAX( vmin, vmax), 0), mask);
		// retira hue do hsv
		cvSplit( hsv, hue, 0, 0, 0 );
		
		// Percorre a lista de marcadores e executa o camshift
		Marker *marker;
		marker = markerList;
		bool reset = false;
		while(marker != NULL){
			if(count <= 0){
				marker->position = camshift(hue, mask, marker->position, marker->hist, &(marker->track_box), true);
				reset = true;
			}else{
				marker->position = camshift(hue, mask, marker->position, marker->hist, &(marker->track_box), false);
			}
			marker = marker->next;
		}
		count--;
		if(reset){
			count = refresh;
		}
		
		cvWaitKey(10); // trocar por sleep
		if(stop)
			break;
		
		handle(frame, markerList);
	}
	
	cvReleaseCapture( &capture );
	cvDestroyWindow("CamShiftDemo"); ////////////
	
}

void addMarker(CvRect position, CvHistogram* hist){
	Marker* m;
	m = (Marker *)malloc(sizeof(Marker));
	m->id = markerId;
	markerId++;
	m->position = position;
	CvBox2D track_box;
	m->track_box = track_box;
	m->hist = hist;
	m->next = NULL;
	if(markerList != NULL){
		Marker* marker = markerList;
		while(marker->next != NULL){
			marker = marker->next;
		}
		marker->next = m;
	}else{
		markerList = m;
	}
	
}

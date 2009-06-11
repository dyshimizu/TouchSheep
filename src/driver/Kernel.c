//
// Kernel.c
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#include "Kernel.h"

#include "Camshift.h"

MarkerList markerList;

void kernelLoop(int cam, int vmin, int vmax, int smin){
	
	markerList = NULL;
	
	cvNamedWindow( "CamShiftDemo", 1 ); /////////////////////////
	
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
		while(marker != NULL){
			marker->position = camshift(hue, mask, marker->position, marker->hist, &(marker->track_box));
			
			if( !frame->origin ){////////////
				marker->track_box.angle = -(marker->track_box.angle);////////////
			}//////////////////
			cvEllipseBox( frame, marker->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );////////////
			
			marker = marker->next;
		}
		
		// termina o camshift... temporário!!!!
		int c;/////////////////
		c = cvWaitKey(10);//////////////
		if( (char) c == 27 ){///////////////
			break;/////////////////
		}////////////////
		
		cvShowImage( "CamShiftDemo", frame ); //////////////////////
	}
	
	cvReleaseCapture( &capture );
	cvDestroyWindow("CamShiftDemo"); ////////////
	
}

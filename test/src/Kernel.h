//
// Kernel.h
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#ifndef KERNEL_H
#define KERNEL_H

#include "cv.h"
#include "highgui.h"

#include "Camshift.h"

typedef struct{
	int thread_id;
	CvCapture* capture;
	void (* handle)(IplImage*, MarkerList);
	int refresh;
	int vmin;
	int vmax;
	int smin;
} kernel_params;

void kernelLoop(CvCapture* capture, void handle(IplImage*, MarkerList), int refresh, int vmin, int vmax, int smin);
void *kernelThread(void *threadarg);
void stopKernelThread();

void addMarker(CvRect position, CvHistogram* hist);

#endif

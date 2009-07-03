#include "TSApplication.h"

// Necessário para o callback do kernel
void fcallback (IplImage* img, MarkerList list);
TSApplication *TSAPPLICATIONPOINTERTOCALLBACK;

TSApplication::TSApplication (CvCapture* cvCapture, int refresh, int vmin, int vmax, int smin){
	
	TSAPPLICATIONPOINTERTOCALLBACK = this;
	
	p.thread_id = 1;
	p.capture = cvCapture;
	p.handle = &fcallback;
	p.refresh = refresh;
	p.vmin = vmin;
	p.vmax = vmax;
	p.smin = smin;
}

int TSApplication::addMarker (CvRect position, CvHistogram* hist, int markerType){
	
}

bool TSApplication::removeMarker (int id){
	
}

int TSApplication::start (){
	return pthread_create(&kthread, NULL, kernelThread, (void *)&p);
}

void TSApplication::stop (){
	stopKernelThread();
}

void TSApplication::addListener (TSListener tsListener){
	
}

void TSApplication::removeAllListeners (){
	
}

void TSApplication::handle (IplImage* img, MarkerList markerList){
	
}

TSApplication::~TSApplication (){
	
}

void fcallback (IplImage* img, MarkerList list){
	TSAPPLICATIONPOINTERTOCALLBACK->handle(img, list);
}

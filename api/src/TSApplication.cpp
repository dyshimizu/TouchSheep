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

int TSApplication::addTSMarker (TSMarker* tsMarker){
	
}

bool TSApplication::removeTSMarker (int id){
	
}

int TSApplication::start (){
	return pthread_create(&kthread, NULL, kernelThread, (void *)&p);
}

void TSApplication::stop (){
	stopKernelThread();
}

void TSApplication::addTSListener (TSListener tsListener){
	
}

void TSApplication::removeAllTSListeners (){
	
}

void TSApplication::handle (IplImage* img, MarkerList markerList){
	
}

TSApplication::~TSApplication (){
	
}

void fcallback (IplImage* img, MarkerList list){
	TSAPPLICATIONPOINTERTOCALLBACK->handle(img, list);
}

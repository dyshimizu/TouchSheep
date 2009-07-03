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

int TSApplication::addTSMarker (TSMarker* tsMarker, int markerType){
	// TODO:
	// Definir TSMarkers
	// Associar tipo e marcador
	// retornar id
}

bool TSApplication::removeTSMarker (int id){
	removeMarker(id);
}

int TSApplication::start (){
	return pthread_create(&kthread, NULL, kernelThread, (void *)&p);
}

void TSApplication::stop (){
	stopKernelThread();
}

void TSApplication::addTSListener (TSListener* tsListener){
	tsListenerList.push_back(tsListener);
}

void TSApplication::removeAllTSListeners (){
	tsListenerList.clear();
}

void TSApplication::handle (IplImage* img, MarkerList markerList){
	// TODO:
	// Percorres os TSListeners e executá-los
	// Mas antes, definí-los
}

TSApplication::~TSApplication (){
	stop();
}

void fcallback (IplImage* img, MarkerList list){
	TSAPPLICATIONPOINTERTOCALLBACK->handle(img, list);
}

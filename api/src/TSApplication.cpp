#include "TSApplication.h"

// Necessário para o callback do kernel
void fcallback (IplImage* img, MarkerList list);
TSApplication *TSAPPLICATIONPOINTERTOCALLBACK;

TSApplication::TSApplication (CvCapture* cvCapture, int refresh, int vmin, int vmax, int smin){
	
	TSAPPLICATIONPOINTERTOCALLBACK = this;
	frame = NULL;
	frameHSV = NULL;
	hue = NULL;
	mask = NULL;
	hist = NULL;
	
	p.thread_id = 1;
	p.capture = cvCapture;
	p.handle = &fcallback;
	p.refresh = refresh;
	p.vmin = vmin;
	p.vmax = vmax;
	p.smin = smin;
}

int TSApplication::addTSMarker (int x1, int y1, int x2, int y2, int markerType){
	if(frame == NULL)
		return -1;
	
	// Calculando a seleção do tipo CvRect
	CvRect selection;
	selection.x = x1;
	selection.y = y1;
	selection.width = x2-x1;
	selection.height = y2-y1;
	
	// Calculando o histograma
	cvInRangeS( frameHSV, cvScalar(0,30,MIN(10,256),0), cvScalar(180,256,MAX(10,256),0), mask );
	cvSplit( frameHSV, hue, 0, 0, 0 );
	hist = getHistogram(hue, mask, selection);
	
	// adicionando o marcador
    addMarker(markerType, selection, hist);
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
	if(!frameHSV){
		frameHSV = cvCreateImage( cvGetSize(img), 8, 3 );
		hue = cvCreateImage( cvGetSize(img), 8, 1 );
		mask = cvCreateImage( cvGetSize(img), 8, 1 );
	}
	frame = img;
	cvCvtColor(img, frameHSV, CV_BGR2HSV);
	
	std::list<TSListener*>::iterator it;
	for ( it=tsListenerList.begin() ; it != tsListenerList.end(); it++ ){
		(*it)->listening(img, markerList);
	}
}

TSApplication::~TSApplication (){
	stop();
}

void fcallback (IplImage* img, MarkerList list){
	TSAPPLICATIONPOINTERTOCALLBACK->handle(img, list);
}

// This file is part of TouchSheep.
// 
//     TouchSheep is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     TouchSheep is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with TouchSheep.  If not, see <http://www.gnu.org/licenses/>.

#include "TouchSheep.h"
#include "TSCaptureException.h"

int TouchSheep::RightThumbFinger = 1;
int TouchSheep::RightIndexFinger = 2;
int TouchSheep::LeftThumbFinger  = 3;
int TouchSheep::LeftIndexFinger  = 4;

// Necessário para o callback do kernel
void fcallback (IplImage* img, MarkerList list);
TouchSheep *TSAPPLICATIONPOINTERTOCALLBACK;

TouchSheep::TouchSheep (int cam, int refresh, int vmin, int vmax, int smin){
	
	TSAPPLICATIONPOINTERTOCALLBACK = this;
	frame = NULL;
	frameHSV = NULL;
	hue = NULL;
	mask = NULL;
	hist = NULL;
	
	CvCapture *cvCapture = cvCaptureFromCAM(cam);
	if(!cvCapture)
		throw tsCaptureException;
	
	p.thread_id = 1;
	p.capture = cvCapture;
	p.handle = &fcallback;
	p.refresh = refresh;
	p.vmin = vmin;
	p.vmax = vmax;
	p.smin = smin;
}

TouchSheep::TouchSheep (const char* filename, int refresh, int vmin, int vmax, int smin){
	TSAPPLICATIONPOINTERTOCALLBACK = this;
	frame = NULL;
	frameHSV = NULL;
	hue = NULL;
	mask = NULL;
	hist = NULL;
	
	CvCapture *cvCapture = cvCreateFileCapture(filename);
	if(!cvCapture)
		throw tsCaptureException;
	
	p.thread_id = 1;
	p.capture = cvCapture;
	p.handle = &fcallback;
	p.refresh = refresh;
	p.vmin = vmin;
	p.vmax = vmax;
	p.smin = smin;
}

int TouchSheep::addTSMarker (int x1, int y1, int x2, int y2, int markerType){
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

bool TouchSheep::removeTSMarker (int id){
	removeMarker(id);
}

int TouchSheep::start (){
	return pthread_create(&kthread, NULL, kernelThread, (void *)&p);
}

void TouchSheep::loop (){
	kernelLoop(p.capture, p.handle, p.refresh, p.vmin, p.vmax, p.smin);
}

void TouchSheep::stop (){
	stopKernelThread();
}

void TouchSheep::addTSListener (TSListener* tsListener){
	tsListenerList.push_back(tsListener);
}

void TouchSheep::removeAllTSListeners (){
	tsListenerList.clear();
}

void TouchSheep::handle (IplImage* img, MarkerList markerList){
	if(!frameHSV){
		frameHSV = cvCreateImage( cvGetSize(img), 8, 3 );
		hue = cvCreateImage( cvGetSize(img), 8, 1 );
		mask = cvCreateImage( cvGetSize(img), 8, 1 );
	}
	frame = img;
	cvCvtColor(img, frameHSV, CV_BGR2HSV);
	
	// converte MarkerList para uma lista de TSMarker
	Marker* m;
	m = markerList;
	while(m){
		TSMarker* tsMarker = new TSMarker;
		tsMarker->id = m->id;
		tsMarker->markerType = m->markerType;
		tsMarker->position.x = m->position.x;
		tsMarker->position.y = m->position.y;
		tsMarker->position.width = m->position.width;
		tsMarker->position.height = m->position.height;
		tsMarker->track_box.center.x = m->track_box.center.x;
		tsMarker->track_box.center.y = m->track_box.center.y;
		tsMarker->track_box.size.width = m->track_box.size.width;
		tsMarker->track_box.size.height = m->track_box.size.height;
		tsMarker->track_box.angle = m->track_box.angle;
		tsMarkerList.push_back(tsMarker);
		m = m->next;
	}
	
	// Chama os listeners cadastrados
	std::list<TSListener*>::iterator it;
	for ( it=tsListenerList.begin() ; it != tsListenerList.end(); it++ ){
		(*it)->listening(img, tsMarkerList);
	}
	
	tsMarkerList.clear();
}

TouchSheep::~TouchSheep (){
	stop();
}

void fcallback (IplImage* img, MarkerList list){
	TSAPPLICATIONPOINTERTOCALLBACK->handle(img, list);
}

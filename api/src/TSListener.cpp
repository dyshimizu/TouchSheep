#include "TSListener.h"

#include "stdio.h"

TSListener::TSListener (){
	
}

TSListener::~TSListener (){
	
}

virtual void TSListener::performed (TSEvent* e){
	
}

void TSListener::listening (IplImage* img, MarkerList markerList){
	TSEvent* e = new TSEvent();
	e->img = img;
	e->markerList = markerList;
	performed(e);
	delete e;
}

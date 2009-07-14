#include "TSTouchMarkerListener.h"

#include <math.h>

TSTouchMarkerListener::TSTouchMarkerListener(int marker1, int marker2){
	marker1Id = marker1;
	marker2Id = marker2;
}

void TSTouchMarkerListener::performed (TSEvent* e){
	TSTouchMarkerEvent *event;
	event = new TSTouchMarkerEvent();
	event->img = e->img;
	event->markerList = e->markerList;
	
	Marker* marker1;
	Marker* marker2;
	Marker* m;
	m = e->markerList;
	while(m){
		if(m->id == marker1Id){
			marker1 = m;
		}else{
			if(m->id == marker2Id){
				marker2 = m;
			}
		}
		m = m->next;
	}
	
	event->marker1 = marker1;
	event->marker2 = marker2;
	
	// distância
	float distance;
	float d1 = (marker1->track_box.center.x)-(marker2->track_box.center.x);
	float d2 = (marker1->track_box.center.y)-(marker2->track_box.center.y);
	distance = sqrt(d1*d1 + d2*d2);
	event->distance = distance;
	
	// proximidade de marker1 e marker2
	
}

void TSTouchMarkerListener::touchPerformed(TSTouchMarkerEvent* e){
	
}

void TSTouchMarkerListener::distancePerformed(TSTouchMarkerEvent* e){
	
}

TSTouchMarkerListener::~TSTouchMarkerListener(){
	
}


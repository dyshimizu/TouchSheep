#include "TSTouchMarkerListener.h"

#include <stdio.h>

TSTouchMarkerListener::TSTouchMarkerListener(int marker1, int marker2){
	marker1Id = marker1;
	marker2Id = marker2;
}

void TSTouchMarkerListener::performed (TSEvent* e){
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
	// calcula distância de marker1 e marker2
	
	// proximidade de marker1 e marker2
	
}

void TSTouchMarkerListener::touchPerformed(TSTouchMarkerEvent* e){
	
}

void TSTouchMarkerListener::distancePerformed(TSTouchMarkerEvent* e){
	
}

TSTouchMarkerListener::~TSTouchMarkerListener(){
	
}


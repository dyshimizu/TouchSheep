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

#include "TSTouchMarkerListener.h"
#include "TSMarker.h"

#include <math.h>

TSTouchMarkerListener::TSTouchMarkerListener(int marker1, int marker2){
	marker1Id = marker1;
	marker2Id = marker2;
	touch = false;
}

void TSTouchMarkerListener::performed (TSEvent* e){
	TSTouchMarkerEvent *event;
	event = new TSTouchMarkerEvent();
	event->img = e->img;
	event->tsMarkerList = e->tsMarkerList;
	
	TSMarker* marker1;
	TSMarker* marker2;
	std::list<TSMarker*>::iterator it;
	for ( it=e->tsMarkerList.begin() ; it != e->tsMarkerList.end(); it++ ){
		if((*it)->id == marker1Id){
			marker1 = (*it);
		}else{
			if((*it)->id == marker2Id){
				marker2 = (*it);
			}
		}
	}
		
	if(marker1 && marker2){
		event->marker1 = marker1;
		event->marker2 = marker2;

		// distância
		float distance;
		float d1 = (marker1->track_box.center.x)-(marker2->track_box.center.x);
		float d2 = (marker1->track_box.center.y)-(marker2->track_box.center.y);
		distance = sqrt(d1*d1 + d2*d2);
		event->distance = distance;

		event->d.x = (marker2->track_box.center.x - marker1->track_box.center.x)/2 + marker1->track_box.center.x;
		event->d.y = (marker2->track_box.center.y - marker1->track_box.center.y)/2 + marker1->track_box.center.y;
		distancePerformed(event);

		// proximidade de marker1 e marker2
		CvPoint p1Marker1;
		p1Marker1.x = marker1->position.x;
		p1Marker1.y = marker1->position.y;
		CvPoint p2Marker1;
		p2Marker1.x = marker1->position.x + marker1->position.width;
		p2Marker1.y = marker1->position.y + marker1->position.height;
		CvPoint p1Marker2;
		p1Marker2.x = marker2->position.x;
		p1Marker2.y = marker2->position.y;
		CvPoint p2Marker2;
		p2Marker2.x = marker2->position.x + marker2->position.width;
		p2Marker2.y = marker2->position.y + marker2->position.height;
		
		// tratamento de colisão simples
		// na verdade é uma possível colisão, pois leva-se em conta somente o retângulo
		// que engloba o marcador, e não o marcador em si.
		release = true;
		if(p1Marker2.x > p1Marker1.x && p1Marker2.y > p1Marker1.y && 
		   p1Marker2.x < p2Marker1.x && p1Marker2.y < p2Marker1.y){
			touch = true;
			release = false;
			touchPerformed(event);
		}else{
			if(p2Marker2.x > p1Marker1.x && p2Marker2.y > p1Marker1.y && 
			   p2Marker2.x < p2Marker1.x && p2Marker2.y < p2Marker1.y){
				touch = true;
				release = false;
				touchPerformed(event);
			}else{
				if(p1Marker1.x > p1Marker2.x && p1Marker1.y > p1Marker2.y && 
				   p1Marker1.x < p2Marker2.x && p1Marker1.y < p2Marker2.y){
					touch = true;
					release = false;
					touchPerformed(event);
				}else{
					if(p2Marker1.x > p1Marker2.x && p2Marker1.y > p1Marker2.y && 
					   p2Marker1.x < p2Marker2.x && p2Marker1.y < p2Marker2.y){
						touch = true;
						release = false;
						touchPerformed(event);
					}
				}
			}
		}
		
		if(release && touch){
			touch = false;
			releasePerformed(event);
		}
		
	}
	delete event;
}

void TSTouchMarkerListener::touchPerformed(TSTouchMarkerEvent* e){
	
}

void TSTouchMarkerListener::releasePerformed(TSTouchMarkerEvent* e){
	
}

void TSTouchMarkerListener::distancePerformed(TSTouchMarkerEvent* e){
	
}

TSTouchMarkerListener::~TSTouchMarkerListener(){
	
}


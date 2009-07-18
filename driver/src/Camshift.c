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

#include "Camshift.h"

#include <stdio.h>

CvRect camshift(IplImage* frame, IplImage* mask, CvRect selection, CvHistogram* hist, CvBox2D *track_box, bool executeConnectedComponents){
	
	CvConnectedComp track_comp;
	
	IplImage* backproject;
	backproject = cvCreateImage( cvGetSize(frame), 8, 1 );
	cvCalcBackProject( &frame, backproject, hist );
	cvAnd( backproject, mask, backproject, 0 );
	
	if(executeConnectedComponents){
		ComponentList clist;
		clist = getConnectedComponents(backproject);
		Component* c;
		c = clist;
		int area = 0;
		Rect rect;
		while(c != NULL){
			if(c->area > area){
				area = c->area;
				rect = c->rect;
			}
			c = c->next;
		}
		selection.x = rect.min.x;
		selection.y = rect.min.y;
		selection.width = rect.max.x - rect.min.x;
		selection.height = rect.max.y - rect.min.y;
	}
	
	cvCamShift( backproject, selection, cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ), &track_comp, track_box );
	
	cvReleaseImage(&backproject);
	
	return track_comp.rect;
}

CvHistogram* getHistogram(IplImage* frame, IplImage* mask, CvRect selection){
	
	int hdims = 16;
	float hranges_arr[] = {0,180};
	float* hranges = hranges_arr;
	
	CvHistogram *hist = 0;
	hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );
		
	float max_val = 0.f;
	cvSetImageROI( frame, selection );
	cvSetImageROI( mask, selection );
	cvCalcHist( &frame, hist, 0, mask );
	cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 );
	cvConvertScale( hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0 );
	cvResetImageROI( frame );
	cvResetImageROI( mask );
	
	return hist;
}

void addMarker(MarkerList* list, int id, int markerType, CvRect position, CvBox2D track_box, CvHistogram *hist){
	Marker* m;
	m = (Marker *)malloc(sizeof(Marker));
	m->id = id;
	m->markerType = markerType;
	m->position = position;
	m->track_box = track_box;
	m->hist = hist;
	m->next = NULL;
	if(*list != NULL){
		Marker* marker = *list;
		while(marker->next != NULL){
			marker = marker->next;
		}
		marker->next = m;
	}else{
		*list = m;
	}
}

bool removeMarker(MarkerList* list, int id){
	if(*list != NULL){
		Marker* marker = *list;
		Marker* aux;
		if(marker->id == id){
			*list = marker->next;
			free(marker);
			return true;
		}
		while(marker->next != NULL){
			if(marker->next->id == id){
				aux = marker->next;
				marker->next = aux->next;
				free(aux);
				return true;
			}
			marker = marker->next;
		}
	}
	return false;
}

void removeAllMarkers(MarkerList* list){
	Marker* marker;
	while(*list != NULL){
		marker = *list;
		*list = marker->next;
		free(marker);
	}
}

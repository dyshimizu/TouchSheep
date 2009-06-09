#include "Camshift.h"

CvRect camshift(IplImage* frame, IplImage* mask, CvRect selection, CvHistogram* hist, CvBox2D *track_box){
	
	CvConnectedComp track_comp;
	
	IplImage* backproject;
	backproject = cvCreateImage( cvGetSize(frame), 8, 1 );
	cvCalcBackProject( &frame, backproject, hist );
	cvAnd( backproject, mask, backproject, 0 );
	
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

void addMarker(MarkerList* list, int id, CvRect position, CvBox2D track_box, CvHistogram *hist){
	Marker* m;
	m = (Marker *)malloc(sizeof(Marker));
	m->id = id;
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

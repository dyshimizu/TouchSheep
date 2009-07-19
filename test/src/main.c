#include "TSCore/TSApplication.h"
#include "TSCore/TSListener.h"
#include "TSCore/TSTouchMarkerListener.h"

#include "stdio.h"

bool ok;
TSApplication* app;

class Teste: public TSTouchMarkerListener{
	
public:
	Teste(int marker1, int marker2): TSTouchMarkerListener (marker1, marker2){
		
	}
	
	void touchPerformed(TSTouchMarkerEvent* e){
		printf("toquei!\n");
	}
	
	void releasePerformed(TSTouchMarkerEvent* e){
		printf("soltei!\n");
	}
	
	void distancePerformed (TSTouchMarkerEvent* e){
		if(!ok){
			app->addTSMarker(335, 76, 369, 97, 1);
			app->addTSMarker(326, 368, 389, 410, 2);
			ok = true;
		}
		//MarkerList list;
		//list = e->markerList;
		//while(list){
		//	cvEllipseBox(e->img, list->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
		//	list = list->next;
		//}
		
		CvPoint p1;
		CvPoint p2;
		cvEllipseBox(e->img, e->marker1->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
		p1.x = e->marker1->position.x;
		p1.y = e->marker1->position.y;
		p2.x = e->marker1->position.x + e->marker1->position.width;
		p2.y = e->marker1->position.y + e->marker1->position.height;
		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
		cvEllipseBox(e->img, e->marker2->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
		p1.x = e->marker2->position.x;
		p1.y = e->marker2->position.y;
		p2.x = e->marker2->position.x + e->marker2->position.width;
		p2.y = e->marker2->position.y + e->marker2->position.height;
		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
		
		p1.x = e->d.x -10;
		p1.y = e->d.y -10;
		p2.x = e->d.x +10;
		p2.y = e->d.y +10;
		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
		
		cvShowImage("Teste", e->img);
	}
	
};

int main(){
	//CvCapture *cam = cvCaptureFromCAM(0);
	
	//ok = false;
	
	cvNamedWindow("Teste");
	
	//CvCapture *cam = cvCreateFileCapture("video.mpg");
	//if(!cam)
	//	return 0;
	
	app = new TSApplication("video.mpg", 30, 10, 256, 30);
	
	TSListener* l;
	l = new Teste(0,1);
	
	app->addTSListener(l);
	
	int i;
	i = app->start();
	
	printf("%d", i);
	scanf("%d",&i);
}

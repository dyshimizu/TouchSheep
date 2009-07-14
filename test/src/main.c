#include "TSApplication.h"
#include "TSListener.h"
#include "TSTouchMarkerListener.h"

#include "stdio.h"

bool ok;
TSApplication* app;

class Teste: public TSTouchMarkerListener{
	
public:
	Teste(int marker1, int marker2): TSTouchMarkerListener (marker1, marker2){
		
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
		
		cvEllipseBox(e->img, e->marker1->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
		cvEllipseBox(e->img, e->marker2->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
		
		CvPoint p1;
		CvPoint p2;
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
	
	ok = false;
	
	cvNamedWindow("Teste");
	
	CvCapture *cam = cvCreateFileCapture("video.mpg");
	if(!cam)
		return 0;
	
	app = new TSApplication(cam, 30, 10, 256, 30);
	
	TSListener* l;
	l = new Teste(0,1);
	
	app->addTSListener(l);
	
	int i;
	i = app->start();
	
	printf("%d", i);
	scanf("%d",&i);
}

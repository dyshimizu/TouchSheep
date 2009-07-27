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
			//app->addTSMarker(222, 336, 243, 350, 1);//verde
			//app->addTSMarker(355, 215, 381, 226, 2);//roxo
			app->addTSMarker(409, 101, 426, 132, 1);//azul
			app->addTSMarker(157, 248, 184, 267, 2);//amarelo
			ok = true;
		}
		//MarkerList list;
		//list = e->markerList;
		//while(list){
		//	cvEllipseBox(e->img, list->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
		//	list = list->next;
		//}
		
		/*CvPoint p1;
		CvPoint p2;
		p1.x = e->marker1->position.x;
		p1.y = e->marker1->position.y;
		p2.x = e->marker1->position.x + e->marker1->position.width;
		p2.y = e->marker1->position.y + e->marker1->position.height;
		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
		//printf("%d,%d \n", p1.x, p1.y);
		//printf("%d,%d \n", p2.x, p2.y);
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
		*/
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
	
	app = new TSApplication("video5.mpg", 30, 10, 256, 30);
	
	TSListener* l;
	l = new Teste(0,1);
	
	app->addTSListener(l);
	
	int i;
	i = app->start();
	
	printf("%d", i);
	scanf("%d",&i);
}

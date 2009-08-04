#include <QApplication>
#include <QLabel>

#include "MyThread.h"
#include "MyLabel.h"

int main(int argc, char **argv){
	QApplication app(argc, argv);
	
	MyLabel ml;
	ml.show();
	
	MyThread mt;
	
	app.connect(&mt, SIGNAL(show(TSImage*)), &ml, SLOT(setValue(TSImage*)));
	
	mt.start();
	
	app.exec();
}


/*#include <TSCore/TSImage.h>
#include <TSGui/TSImageDisplay.h>
#include <TSCore/TouchSheep.h>
#include <TSCore/TSListener.h>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QThread>

#include <cv.h>
#include <highgui.h>

#include <stdio.h>

class MyTSImageDisplay: public QLabel{
public:
	void setTSImage(TSImage *tsImg){
		QImage qImage = QImage( (unsigned char *)tsImg->imageData, tsImg->width, tsImg->height, 
								tsImg->widthStep, QImage::Format_RGB888);
		QPixmap pm = QPixmap::fromImage(qImage,0);
		
		setPixmap(pm);
	}
public slots:
     void setValue(TSImage *img){
		setTSImage(img);
	}
};

MyTSImageDisplay *tsid;

class MyListener: public TSListener{
	
	void performed (TSEvent* e){
		
	}
	
};

class MyThread : public QThread {
private:
	void show();

public:
	void run(){
		
		IplImage *img = 0;
		img = cvLoadImage( "foto1.jpg", CV_LOAD_IMAGE_UNCHANGED );
		cvConvertImage(img, img, CV_CVTIMG_SWAP_RB);
		TSImage *tsImage;
		tsImage = new TSImage();
		tsImage->imageData = img->imageData;
		tsImage->width = img->width;
		tsImage->height = img->height;
		tsImage->widthStep = img->widthStep;
        
		for( int count = 0; count < 20; count++ ) {
			show();
		}
		
	}
};

int main(int argc, char *argv[]){
	QApplication *app = new QApplication(argc, argv);
	
	//TouchSheep *ts = new TouchSheep("video5.mpg", 30, 10, 256, 30);
	
	//MyListener *listener = new MyListener();
	//ts->addTSListener(listener);
	
	//QLabel *label = new QLabel("Label");
	//label->show();
	
	tsid = new MyTSImageDisplay();
	tsid->show();
	
	MyThread a;
	
	//app->connect(&a, SIGNAL(show(TSImage*)), &tsid, SLOT(setValue(TSImage*)));
	
	//a.start();
	
	//int ret = ts->start();
	
	//printf("%d\n", ret);
	
	app->exec();
}
*/
//#include "TSCore/TSApplication.h"
//#include "TSCore/TSListener.h"
//#include "TSCore/TSTouchMarkerListener.h"
//
//#include "stdio.h"
//
//bool ok;
//TSApplication* app;
//
//class Teste: public TSTouchMarkerListener{
//	
//public:
//	Teste(int marker1, int marker2): TSTouchMarkerListener (marker1, marker2){
//		
//	}
//	
//	void touchPerformed(TSTouchMarkerEvent* e){
//		printf("toquei!\n");
//	}
//	
//	void releasePerformed(TSTouchMarkerEvent* e){
//		printf("soltei!\n");
//	}
//	
//	void distancePerformed (TSTouchMarkerEvent* e){
//		if(!ok){
//			//app->addTSMarker(222, 336, 243, 350, 1);//verde
//			//app->addTSMarker(355, 215, 381, 226, 2);//roxo
//			app->addTSMarker(409, 101, 426, 132, 1);//azul
//			app->addTSMarker(157, 248, 184, 267, 2);//amarelo
//			ok = true;
//		}
//		//MarkerList list;
//		//list = e->markerList;
//		//while(list){
//		//	cvEllipseBox(e->img, list->track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
//		//	list = list->next;
//		//}
//		
//		/*CvPoint p1;
//		CvPoint p2;
//		p1.x = e->marker1->position.x;
//		p1.y = e->marker1->position.y;
//		p2.x = e->marker1->position.x + e->marker1->position.width;
//		p2.y = e->marker1->position.y + e->marker1->position.height;
//		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
//		//printf("%d,%d \n", p1.x, p1.y);
//		//printf("%d,%d \n", p2.x, p2.y);
//		p1.x = e->marker2->position.x;
//		p1.y = e->marker2->position.y;
//		p2.x = e->marker2->position.x + e->marker2->position.width;
//		p2.y = e->marker2->position.y + e->marker2->position.height;
//		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
//		
//		p1.x = e->d.x -10;
//		p1.y = e->d.y -10;
//		p2.x = e->d.x +10;
//		p2.y = e->d.y +10;
//		cvRectangle(e->img, p1, p2, CV_RGB(255,0,0), 3, CV_AA, 0);
//		*/
//		cvShowImage("Teste", e->img);
//	}
//	
//};
//
//int main(){
//	//CvCapture *cam = cvCaptureFromCAM(0);
//	
//	//ok = false;
//	
//	cvNamedWindow("Teste");
//	
//	//CvCapture *cam = cvCreateFileCapture("video.mpg");
//	//if(!cam)
//	//	return 0;
//	
//	app = new TSApplication("video5.mpg", 30, 10, 256, 30);
//	
//	TSListener* l;
//	l = new Teste(0,1);
//	
//	app->addTSListener(l);
//	
//	int i;
//	i = app->start();
//	
//	printf("%d", i);
//	scanf("%d",&i);
//}
//
#include "TSListenerDisplayVideo.h"

#include <TSCore/TouchSheep.h>

TSListenerDisplayVideo::TSListenerDisplayVideo (char* name, TouchSheep* ts): TSListenerDisplay(name){
	this->name = name;
	touchSheep = ts;
}

TSListenerDisplayVideo::~TSListenerDisplayVideo (){
	
}

void TSListenerDisplayVideo::performed (TSEvent* e){	
	cvRectangle(e->img, cvPoint(300,220), cvPoint(340,260), cvScalar(255));
	std::list<TSMarker*>::iterator it;
	for ( it=e->tsMarkerList.begin() ; it != e->tsMarkerList.end(); it++ ){
		int x11 = (*it)->position.x;
		int x12 = (*it)->position.y;
		int x21 = x11 + (*it)->position.width;
		int x22 = x12 + (*it)->position.height;
		cvRectangle(e->img, cvPoint(x11,x12), cvPoint(x21,x22), cvScalar(255));
	}
	cvShowImage(name, e->img);
	int key = cvWaitKey(10);
	switch(key){
		case 27:
			exit(0);
			break;
		case 32:
			// adicionar marcador
			touchSheep->addTSMarker(300, 220, 340, 260, 0);
			break;
		case 65288:
			// remover marcador
			break;
		case 10:
			// inicar a aplicação
			break;
	}
	//if(key!=-1){
	//	printf("%d\n", key);
	//	printf("%d\n", cvWaitKey(10));
	//}
}

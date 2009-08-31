#include "TSListenerDisplayVideo.h"

TSListenerDisplayVideo::TSListenerDisplayVideo (char* name): TSListenerDisplay(name){
	this->name = name;
}

TSListenerDisplayVideo::~TSListenerDisplayVideo (){
	
}

void TSListenerDisplayVideo::performed (TSEvent* e){	
	cvRectangle(e->img, cvPoint(300,220), cvPoint(340,260), cvScalar(255));
	cvShowImage(name, e->img);
}

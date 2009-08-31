#include "TSListenerDisplay.h"

#include <highgui.h>

TSListenerDisplay::TSListenerDisplay (char* name){
	this->name = name;
}

TSListenerDisplay::~TSListenerDisplay (){
	
}

void TSListenerDisplay::performed (TSEvent* e){
	cvShowImage(name, e->img);
}
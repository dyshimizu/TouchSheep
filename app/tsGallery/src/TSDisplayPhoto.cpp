#include "TSDisplayPhoto.h"

#include <TSCore/TouchSheep.h>

TSDisplayPhoto::TSDisplayPhoto(char* name, char* photo, TouchSheep* ts): TSDisplay(name){
	run = true;
	touchSheep = ts;
	this->name = name;
	this->img = cvLoadImage(photo, 1);
	
	uchar* data = (uchar *)img->imageData;
	int step = img->widthStep/sizeof(uchar);
	int channel = img->nChannels;
	int i;
	int w = img->width;
	int h = img->height;
	for (i = 0; i < h; i++){
		data[(i)*step+(0)*channel] = 0;
		data[(i)*step+(0)*channel+1] = 0;
		data[(i)*step+(0)*channel+2] = 0;
    
		data[(i)*step+(w-1)*channel] = 0;
		data[(i)*step+(w-1)*channel+1] = 0;
		data[(i)*step+(w-1)*channel+2] = 0;
	}
	for (i = 0; i < w; i++){
		data[(0)*step+(i)*channel] = 0;
		data[(0)*step+(i)*channel+1] = 0;
		data[(0)*step+(i)*channel+2] = 0;
    
		data[(h-1)*step+(i)*channel] = 0;
		data[(h-1)*step+(i)*channel+1] = 0;
		data[(h-1)*step+(i)*channel+2] = 0;
	}
	
	this->dst = cvCloneImage(this->img);
}

TSDisplayPhoto::~TSDisplayPhoto(){
	
}

void TSDisplayPhoto::stop(){
	cvDestroyWindow(name);
	run = false;
}

bool TSDisplayPhoto::isRun(){
	return run;
}

void TSDisplayPhoto::show(int angle, float factor){
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	int w = img->width;
	int h = img->height;
	m[0] = (float)(factor*cos(-angle*CV_PI/180.));
	m[1] = (float)(factor*sin(-angle*CV_PI/180.));
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w*0.5f;  
	m[5] = h*0.5f;
	cvGetQuadrangleSubPix( img, dst, &M);
	cvShowImage(name, dst);
}

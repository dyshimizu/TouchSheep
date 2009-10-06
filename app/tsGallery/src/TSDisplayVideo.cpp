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

#include "TSDisplayVideo.h"

#include <TSCore/TouchSheep.h>

#include <stdio.h>

TSDisplayVideo::TSDisplayVideo(char* name, TouchSheep* ts): TSDisplay(name){
	run = true;
	tsListenerDisplayVideo = new TSListenerDisplayVideo(name, ts, this);
	touchSheep = ts;
	this->name = name;
}

TSDisplayVideo::~TSDisplayVideo(){
	
}

void TSDisplayVideo::on_mouse( int event, int x, int y, int flags, void* param ){
	
}

void TSDisplayVideo::stop(){
	run = false;
}

void TSDisplayVideo::start(){
	run = true;
}

bool TSDisplayVideo::isRun(){
	return run;
}

void TSDisplayVideo::showImage(char* filename, int zoom, int angle){
	IplImage* img = cvLoadImage(filename, 1);
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
	
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	m[0] = (float)(zoom*cos(-angle*CV_PI/180.));
	m[1] = (float)(zoom*sin(-angle*CV_PI/180.));
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w*0.5f;  
	m[5] = h*0.5f;
	cvGetQuadrangleSubPix( img, img, &M);
	cvShowImage(name, img);
}


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
#include "TSTouchMarkerListenerPaint.h"

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
	img = cvLoadImage("fundo.bmp", 1);
	cvShowImage(name, img);
	TSTouchMarkerListenerPaint* tsTouchMarkerListenerPaint = new TSTouchMarkerListenerPaint(0,1, this);
	touchSheep->addTSListener((TSListener*)(tsTouchMarkerListenerPaint));
}

bool TSDisplayVideo::isRun(){
	return run;
}

void TSDisplayVideo::putPixel(int x, int y){
	uchar* data = (uchar *)img->imageData;
	int step = img->widthStep/sizeof(uchar);
	int channel = img->nChannels;
	
	data[(x)*step+(y)*channel] = 255;
	data[(x)*step+(y)*channel+1] = 255;
	data[(x)*step+(y)*channel+2] = 255;
	
	data[(x+1)*step+(y)*channel] = 255;
	data[(x+1)*step+(y)*channel+1] = 255;
	data[(x+1)*step+(y)*channel+2] = 255;
	
	data[(x+1)*step+(y+1)*channel] = 255;
	data[(x+1)*step+(y+1)*channel+1] = 255;
	data[(x+1)*step+(y+1)*channel+2] = 255;
	
	data[(x)*step+(y+1)*channel] = 255;
	data[(x)*step+(y+1)*channel+1] = 255;
	data[(x)*step+(y+1)*channel+2] = 255;
	
	cvShowImage(name, img);
}

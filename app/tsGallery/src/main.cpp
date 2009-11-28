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

#include <TSCore/TouchSheep.h>

#include "TSDisplayVideo.h"
#include "TSListenerPhoto.h"

#include <stdio.h>
#include <unistd.h>

#include <highgui.h>

int main(){
	
	// instancia a interface
	TouchSheep* touchSheep = new TouchSheep(0, 30, 10, 256, 30);
	
	// cria o display para visualizar o vídeo
	TSDisplayVideo *tsDisplayVideo = new TSDisplayVideo("tsGallery", touchSheep);
	touchSheep->addTSListener((TSListener*)(tsDisplayVideo->tsListenerDisplayVideo));
	
	// inicia a interface
	touchSheep->start();
	
	while(tsDisplayVideo->isRun()){
		sleep(1);
	}
	
	//touchSheep->removeAllTSListeners();
	//
	//tsDisplayVideo->start();
	//
	//TSListenerPhoto* tsListenerPhoto = new TSListenerPhoto(0,1,1);
	//TSListenerPhoto* tsListenerPhoto2 = new TSListenerPhoto(2,3,2);
	//touchSheep->addTSListener((TSListener*)(tsListenerPhoto));
	//touchSheep->addTSListener((TSListener*)(tsListenerPhoto2));
	//
	//while(tsDisplayVideo->isRun()){
	//	if(tsListenerPhoto->touch)
	//		tsDisplayVideo->showImage("img1.jpg", tsListenerPhoto->zoom, tsListenerPhoto->angle);
	//	if(tsListenerPhoto2->touch)
	//		tsDisplayVideo->showImage("img1.jpg", tsListenerPhoto2->zoom, tsListenerPhoto2->angle);
	//	if(cvWaitKey(20) == 27)
	//		break;
	//}
	
	touchSheep->removeAllTSListeners();
	tsDisplayVideo->start("img.bmp");
	
	char c;
	double zoom = 1.1;
	int angle = 0;
	while(tsDisplayVideo->isRun()){
		c = cvWaitKey(20);
		if(c == 'w'){
			zoom += 0.1;
			tsDisplayVideo->showImage(zoom, angle);
		}else if(c == 's'){
			zoom -= 0.1;
			tsDisplayVideo->showImage(zoom, angle);
		}else if(c == 'a'){
			angle += 5;
			tsDisplayVideo->showImage(zoom, angle);
		}else if(c == 'd'){
			angle -= 5;
			tsDisplayVideo->showImage(zoom, angle);
		}
		if(c == 27){
			break;
		}
	}
	
	return 0;
}

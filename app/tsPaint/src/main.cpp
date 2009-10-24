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

#include <stdio.h>
#include <unistd.h>

#include <highgui.h>

int main(){
	
	// instancia a interface
	TouchSheep* touchSheep = new TouchSheep("video.mpg", 30, 10, 256, 30);
	
	// cria o display para visualizar o vídeo
	TSDisplayVideo *tsDisplayVideo = new TSDisplayVideo("tsGallery", touchSheep);
	touchSheep->addTSListener((TSListener*)(tsDisplayVideo->tsListenerDisplayVideo));
	
	// inicia a interface
	touchSheep->start();
	
	while(tsDisplayVideo->isRun()){
		sleep(1);
	}
	
	touchSheep->removeAllTSListeners();
	tsDisplayVideo->start();
	
	char c;
	while(tsDisplayVideo->isRun()){
		c = cvWaitKey(20);
		if(c == 27){
			break;
		}
	}
	
	return 0;
}

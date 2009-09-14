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
#include "TSDisplayPhoto.h"

#include <stdio.h>
#include <unistd.h>

#include <highgui.h>

int main(){
	
	// instancia a interface
	TouchSheep* touchSheep = new TouchSheep("video5.mpg", 30, 10, 256, 30);
	
	// cria o display para visualizar o vídeo
	TSDisplayVideo *tsDisplayVideo = new TSDisplayVideo("tsGallery - Calibrando..", touchSheep);
	touchSheep->addTSListener((TSListener*)(tsDisplayVideo->tsListenerDisplayVideo));
	
	// inicia a interface
	touchSheep->start();
	
	while(tsDisplayVideo->isRun()){
		sleep(1);
	}
	
	touchSheep->removeAllTSListeners();
	
	TSDisplayPhoto* tsDisplayPhoto = new TSDisplayPhoto("TSGallery", "foto.jpg", touchSheep);
	while(tsDisplayPhoto->isRun()){
		tsDisplayPhoto->show(45, 1.7);
		if( cvWaitKey(30) == 27 )
			break;
	}
	
	return 0;
}
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

#include "TSListenerPhoto.h"
#include "TSDisplayVideo.h"

TSListenerPhoto::TSListenerPhoto(int marker1, int marker2, TSDisplayVideo* tsdv):TSTouchMarkerListener (marker1, marker2){
	tsDisplayVideo = tsdv;
	x = -1;
	w = -1;
	angle = 0;
	zoom = 1.1;
}

void TSListenerPhoto::touchPerformed(TSTouchMarkerEvent* e){
	//printf("touch\n");
	if(x < 0 || w < 0){
		x = e->marker1->position.x;
		w = e->marker1->position.width;
	}
	//float z = zoom + ((float)w-(float)e->marker1->position.width)/10;
	//if(z < 0)
	//	z = 0.1;
	//if(z > 2)
	//	z = 1.9;
	printf("%d\n", (w-e->marker1->position.width));
	tsDisplayVideo->showImage(zoom, angle + (e->marker1->position.x - x));
}

void TSListenerPhoto::releasePerformed(TSTouchMarkerEvent* e){
	angle += (e->marker1->position.x - x);
	//zoom += ((float)w-(float)e->marker1->position.width)/10;
	x = -1;
	w = -1;
	//printf("relese\n");
	//tsDisplayVideo->showImage(0.9, 80);
}


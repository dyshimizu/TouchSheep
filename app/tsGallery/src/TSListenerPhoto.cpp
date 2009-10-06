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

TSListenerPhoto::TSListenerPhoto(int marker1, int marker2, int i):TSTouchMarkerListener (marker1, marker2){
	zoom = 1;
	angle = 0;
	touch = false;
	x = i;
}

void TSListenerPhoto::touchPerformed(TSTouchMarkerEvent* e){
	touch = true;
	if(x==1){
		zoom = 1;
		angle = 10;
	}
	else{
		zoom = 1.7;
		angle = 45;
	}
	printf("%d",x);
}

void TSListenerPhoto::releasePerformed(TSTouchMarkerEvent* e){
	touch = false;
}

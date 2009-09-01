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

#ifndef TSDISPLAYVIDEO_H
#define TSDISPLAYVIDEO_H

#include <TSGui/TSDisplay.h>

#include "TSListenerDisplayVideo.h"

class TouchSheep;

class TSDisplayVideo: public TSDisplay
{
public:
	TSDisplayVideo(char* name, TouchSheep *ts);
	virtual ~TSDisplayVideo();
	virtual void on_mouse( int event, int x, int y, int flags, void* param );
	
	TSListenerDisplayVideo* tsListenerDisplayVideo;
	
private:
	TouchSheep *touchSheep;
};

#endif
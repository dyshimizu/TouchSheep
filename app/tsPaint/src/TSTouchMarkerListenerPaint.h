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

#ifndef TSTOUCHMARKERLISTENERPAINT_H
#define TSTOUCHMARKERLISTENERPAINT_H

#include <TSCore/TSTouchMarkerListener.h>

#include "TSDisplayVideo.h"

class TSTouchMarkerListenerPaint: public TSTouchMarkerListener
{
public:
	TSTouchMarkerListenerPaint(int marker1, int marker2, TSDisplayVideo *tsDV);
	void touchPerformed(TSTouchMarkerEvent* e);
	void releasePerformed(TSTouchMarkerEvent* e);
	
	TSDisplayVideo *tsDisplayVideo;
};

#endif

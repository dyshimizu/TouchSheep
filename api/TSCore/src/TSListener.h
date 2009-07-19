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

#ifndef TSLISTENER_H
#define TSLISTENER_H

#include <stdio.h>
#include <list>

#include "TSKernel.h"

#include "TSEvent.h"

#include "TSMarker.h"

class TSListener
{
public:
	TSListener ();
	virtual ~TSListener ();
	
	virtual void performed (TSEvent* e);

	void listening (IplImage* img, std::list<TSMarker*> tsMarkerList);// TODO
	
};

#endif

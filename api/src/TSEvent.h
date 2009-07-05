#ifndef TSEVENT_H
#define TSEVENT_H

#include "TSKernel.h"

class TSEvent
{
public:
	TSEvent ();
	virtual ~TSEvent ();
	
	IplImage* img;
	MarkerList markerList;
};

#endif
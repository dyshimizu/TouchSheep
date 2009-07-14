#ifndef TSTOUCHMARKEREVENT_H
#define TSTOUCHMARKEREVENT_H

#include "TSKernel.h"

#include "TSEvent.h"

class TSTouchMarkerEvent: public TSEvent
{
public:
	TSTouchMarkerEvent ();
	virtual ~TSTouchMarkerEvent ();
	
	float distance;
	CvPoint d;	
	
};

#endif
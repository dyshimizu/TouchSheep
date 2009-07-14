#ifndef TSTOUCHMARKEREVENT_H
#define TSTOUCHMARKEREVENT_H

#include "TSKernel.h"

#include "TSEvent.h"

class TSTouchMarkerEvent: public TSEvent
{
public:
	TSTouchMarkerEvent ();
	virtual ~TSTouchMarkerEvent ();
	
	Marker *marker1;
	Marker *marker2;
	
	float distance;
	CvPoint d;	
	
};

#endif
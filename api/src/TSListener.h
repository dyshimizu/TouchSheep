#ifndef TSLISTENER_H
#define TSLISTENER_H

#include "TSKernel.h"

#include "TSEvent.h"

class TSListener
{
public:
	TSListener ();
	virtual ~TSListener ();
	
	void performed (TSEvent* e);

	void listening (IplImage* img, MarkerList markerList);
	
};

#endif

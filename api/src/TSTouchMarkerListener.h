#ifndef TSTOUCHMARKERLISTENER_H
#define TSTOUCHMARKERLISTENER_H

#include "TSKernel.h"

#include "TSListener.h"
#include "TSTouchMarkerEvent.h"

class TSTouchMarkerListener: public TSListener{
	
public:
	// Construtor
	TSTouchMarkerListener (int marker1, int marker2);
	
	// Destrutor
	virtual ~TSTouchMarkerListener ();
	
	virtual void touchPerformed(TSTouchMarkerEvent* e);
	
	// performed da classe pai TSListener
	void performed (TSEvent* e);

private:
	int marker1Id;
	int marker2Id;
	
};

#endif

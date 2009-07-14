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
	
	// Chamado quando os marcadores se tocam
	virtual void touchPerformed(TSTouchMarkerEvent* e);
	
	// Chamado quando os marcadores se desencostam
	virtual void releasePerformed(TSTouchMarkerEvent* e);
	
	// Chamado a cada frame e retorna a distância dos centros de cada marcador
	virtual void distancePerformed(TSTouchMarkerEvent* e);
	
	// performed da classe pai TSListener
	void performed (TSEvent* e);

private:
	int marker1Id;
	int marker2Id;
	bool touch;
	bool release;
	
};

#endif

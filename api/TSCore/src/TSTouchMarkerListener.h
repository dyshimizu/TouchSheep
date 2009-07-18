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

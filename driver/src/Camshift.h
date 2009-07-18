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

#ifndef CAMSHIFT_H
#define CAMSHIFT_H

#include "cv.h"
#include "highgui.h"

#include "ConnectedComponent.h"

// Estrutura de dados para entrada no algoritmo do camshift.
// É usada para rastrear mais de um marcador.
typedef struct SMarker{
	int id;
	int markerType;
	CvRect position;
	CvBox2D track_box;
	CvHistogram *hist;
	SMarker *next;
}
Marker;

// Lista de marcadores para o camshift
typedef Marker* MarkerList;

// Retorna a posição do objeto
CvRect camshift(IplImage* frame, IplImage* mask, CvRect selection, CvHistogram* hist, CvBox2D *track_box, bool executeConnectedComponents);

// Calcula histograma
CvHistogram* getHistogram(IplImage* frame, IplImage* mask, CvRect position);

// Adiciona marcador na lista
void addMarker(MarkerList* list, int id, int markerType, CvRect position, CvBox2D track_box, CvHistogram *hist);

// Remove marcador da lista
bool removeMarker(MarkerList* list, int id);

// Remove todos os marcadores da lista
void removeAllMarkers(MarkerList* list);

#endif

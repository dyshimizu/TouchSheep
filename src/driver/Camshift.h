//
// Camshift.h
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#ifndef CAMSHIFT_H
#define CAMSHIFT_H

#include "cv.h"
#include "highgui.h"

// Estrutura de dados para entrada no algoritmo do camshift.
// É usada para rastrear mais de um marcador.
typedef struct SMarker{
	int id;
	CvRect position;
	CvBox2D track_box;
	CvHistogram *hist;
	SMarker *next;
}
Marker;

// Lista de marcadores para o camshift
typedef Marker* MarkerList;

// Retorna a posição do objeto
CvRect camshift(IplImage* frame, IplImage* mask, CvRect selection, CvHistogram* hist, CvBox2D *track_box);

// Calcula histograma
CvHistogram* getHistogram(IplImage* frame, IplImage* mask, CvRect position);

// Adiciona marcador na lista
void addMarker(MarkerList* list, int id, CvRect position, CvBox2D track_box, CvHistogram *hist);

// Remove marcador na lista
bool removeMarker(MarkerList* list, int id);

#endif

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
typedef struct SCamshiftImage{
	int id;
	CvRect position;
	CvHistogram *hist;
	SCamshiftImage *next;
}
CamshiftImage;

// Lista de marcadores para o camshift
typedef CamshiftImage* CamshiftImageList;

// Retorna a posição do objeto
CvRect camshift(IplImage* frame, CvRect position, CvHistogram* hist);

// Calcula histograma
CvHistogram* getHistogram(IplImage* frame, CvRect position);

#endif
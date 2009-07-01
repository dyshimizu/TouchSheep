//
// Kernel.h
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#ifndef TSKERNEL_H
#define TSKERNEL_H

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

// Calcula histograma
CvHistogram* getHistogram(IplImage* frame, IplImage* mask, CvRect position);

// Adicionar um marcador
void addMarker(CvRect position, CvHistogram* hist);

// Parametros que devem ser passado para a thread de kernelLoop
typedef struct{
	int thread_id;
	CvCapture* capture;
	void (* handle)(IplImage*, MarkerList);
	int refresh;
	int vmin;
	int vmax;
	int smin;
} kernel_params;

// Função usada para criar uma thread do loop do kernel
void *kernelThread(void *threadarg);

// Para a thread kernelLoop
void stopKernelThread();

#endif

//
// Kernel.h
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#ifndef KERNEL_H
#define KERNEL_H

#include "cv.h"
#include "highgui.h"

#include "Camshift.h"

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

// Loop do kernel
void kernelLoop(CvCapture* capture, void handle(IplImage*, MarkerList), int refresh, int vmin, int vmax, int smin);

// Função usada para criar uma thread do loop do kernel
void *kernelThread(void *threadarg);

// Para a thread kernelLoop
void stopKernelThread();

// Adiciona marcador
void addMarker(CvRect position, CvHistogram* hist);

// Remove todos os marcadores
void removeAllMarkers();

// Remove um marcador identificado pelo id
bool removeMarker(int id);

#endif

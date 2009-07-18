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
int addMarker(int markerType, CvRect position, CvHistogram* hist);

// Remove todos os marcadores
void removeAllMarkers();

// Remove um marcador identificado pelo id
bool removeMarker(int id);

#endif

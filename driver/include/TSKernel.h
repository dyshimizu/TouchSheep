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

#ifndef TSKERNEL_H
#define TSKERNEL_H

#include "cv.h"
#include "highgui.h"

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

// Calcula histograma
CvHistogram* getHistogram(IplImage* frame, IplImage* mask, CvRect position);

// Adicionar um marcador
void addMarker(int markerType, CvRect position, CvHistogram* hist);

// Remove um marcador identificado pelo id
bool removeMarker(int id);

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

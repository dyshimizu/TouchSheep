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

#ifndef TSAPPLICATION_H
#define TSAPPLICATION_H

#include <list>
#include <stdio.h>

#include "TSKernel.h"

#include <pthread.h>

#include "TSListener.h"
#include "TSMarker.h"

class TSApplication
{
public:
	// Construtor
	// Inicia uma aplicação TouchSheep utilizando como dispositivo de
	// entrada uma câmera
	TSApplication (int cam, int refresh, int vmin, int vmax, int smin);
	
	// Construtor
	// Inicia uma aplicação TouchSheep utilizando como dispositivo de
	// entrada um arquivo de video
	TSApplication (const char* filename, int refresh, int vmin, int vmax, int smin);
	
	// Adiciona marcador
	// Dada TSMarker, é adicionado um marcador de id
	// retornando pela função
	int addTSMarker (int x1, int y1, int x2, int y2, int markerType);
	
	// Tipos de marcadores
	static int RightThumbFinger;
	static int RightIndexFinger;
	static int LeftThumbFinger;
	static int LeftIndexFinger;
	
	// Remove marcador
	// Dado um id, o marcador correspondente é removido.
	// Se a operação for realizada com sucesso, retorna-se true, caso
	// contrário retorna-se false
	bool removeTSMarker (int id);
	
	// Inicia o kernel TouchSheep
	int start ();
	
	// Para o kernel TouchSheep
	void stop ();
	
	// Adiciona um Listener
	// tsListener é adicionado em uma lista de TSListener que é chamado em
	// handle (método que executa uma ação a cada frame capturado pelo
	// kernel)
	void addTSListener (TSListener* tsListener);
	
	// Remove todos os Listeners
	void removeAllTSListeners ();
	
	// Handle chamado a cada laço do kernel
	// Recebe cada frame e a lista de marcadores contendo suas posições
	void handle (IplImage* img, MarkerList markerList);
	
	// Destrutor
	virtual ~TSApplication ();

private:
	// Parametros do kernel
	kernel_params p;
	
	// thread do kernel
	pthread_t kthread;
	
	// Frame atual em RGB
	IplImage* frame;
	
	// Frame atua em HSV
	IplImage* frameHSV;
	
	// Hue de HSV
	IplImage* hue;
	
	// Mascara para gerar o histograma
	IplImage* mask;
	
	// Histograma
	CvHistogram *hist;
	
	// Lista de Marcadores
	std::list<TSMarker*> tsMarkerList;
	
	// Lista de Listeners
	std::list<TSListener*> tsListenerList;
};

#endif

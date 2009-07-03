#ifndef TSAPPLICATION_H
#define TSAPPLICATION_H

#include <list>
#include <stdio.h>

#include "TSKernel.h"

#include "highgui.h"

#include <pthread.h>

#include "TSListener.h"

class TSApplication
{
public:
	// Construtor
	// Inicia uma aplicação TouchSheep utilizando como entrada
	// o cvCapture passado por parâmetro
	TSApplication (CvCapture* cvCapture, int refresh, int vmin, int vmax, int smin);
	
	// Adiciona marcador
	// Dada uma posição e um histograma, é adicionado um marcador de id
	// retornando pela função
	int addMarker (CvRect position, CvHistogram* hist, int markerType);
	
	// Remove marcador
	// Dado um id, o marcador correspondente é removido.
	// Se a operação for realizada com sucesso, retorna-se true, caso
	// contrário retorna-se false
	bool removeMarker (int id);
	
	// Inicia o kernel TouchSheep
	int start ();
	
	// Para o kernel TouchSheep
	void stop ();
	
	// Adiciona um Listener
	// tsListener é adicionado em uma lista de TSListener que é chamado em
	// handle (método privado que executa uma ação a cada frame capturado pelo
	// kernel)
	void addListener (TSListener tsListener);
	
	// Remove todos os Listeners
	void removeAllListeners ();
	
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
	
	// tipos de marcadores
	// -> adicionar os tipos aqui
	
	// Lista de Listeners
	std::list<TSListener> tsListenerList;
};

#endif

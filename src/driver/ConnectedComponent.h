//
// ConnectedComponent.h
//
// Ígor Bonadio & Daniel Shimizu Yutaka
// 2009
//

#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include "cv.h"
#include "highgui.h"

#define INTLEN 65535

typedef struct {
	CvPoint min; // ponto superior esquerdo do retângulo
	CvPoint max; // ponto inferior direito do retângulo
} 
Rect;

typedef struct SComponent{
	int color;
	long area;
	Rect rect;
	SComponent *next;
}
Component;

typedef Component* ComponentList;

// Retorna o maior componente conectado na imagem em tons de cinza
// passada por parâmetro
ComponentList getConnectedComponents(IplImage* img);

// Cria um novo componente conectado
Component* newComponent();

// Adiciona um componente conectado
void addComponent(ComponentList* list, int color, long area, Rect rect);

// Retorna o componente conectado que possui a cor passada por parâmetro
Component* getComponent(ComponentList list, int color);

Rect createRect(int x1, int y1, int x2, int y2);
Rect addPointToRect(int x, int y, Rect rect);
Rect joinRects(Rect r1, Rect r2);

#endif

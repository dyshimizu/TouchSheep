/*************************************************************************
cabeçalho
*************************************************************************/

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
	SComponent *next;
}
Component;

typedef Component* ComponentList;

// Retorna o maior componente conectado na imagem em tons de cinza
// passada por parâmetro
ComponentList getConnectedComponents(IplImage* img);

Component* newComponent();
void addComponent(ComponentList* list, int color, long area);
Component* getComponent(ComponentList list, int color);

#endif
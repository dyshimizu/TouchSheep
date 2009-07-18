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

// Remove todos os componentes conectados da lista
void removeAllComponents(ComponentList* list);

Rect createRect(int x1, int y1, int x2, int y2);
Rect addPointToRect(int x, int y, Rect rect);
Rect joinRects(Rect r1, Rect r2);

#endif

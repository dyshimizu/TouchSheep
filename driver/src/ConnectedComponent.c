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

#include "ConnectedComponent.h"


#include <stdio.h>


ComponentList getConnectedComponents(IplImage* img){
	// TODO: Melhorar matrixColor, pois é um vetor muito grande
	//		 Calcular o centro de massa talvez seja uma boa solução...
	
	int i, j;											// contadores para o for
	
	unsigned int matrixLabel[img->height][img->width]; 	// matriz do mesmo tamanho da imagem img
														// contendo os labels de cada pixel
														
	unsigned int matrixColor[INTLEN];					// matriz contendo a cor de cada label,
														// sendo matrixColor[label] = cor
														
	unsigned long matrixSize[INTLEN];					// matriz contendo a quantidade de pixel
														// de cada label, sendo matrixSize[label] = cor
														
	Rect matrixRect[INTLEN];							// matriz contendo o retângulo da posição do
														// label, sendo matrixRect[label] = posição
														
	unsigned int label = 0;								// contador de labels
	
	unsigned int color = 0;								// contador de cores
	
	uchar* data = (uchar *)img->imageData;				// data contem os pixels da imagem img, que para
	int step = img->widthStep/sizeof(uchar);			// percorrê-la utiliza-se step e channel.
	int channel = img->nChannels;						// data[(i)*step+(j)*channel] para um pixel i,j
	
	// Zera os pixels da primeira linha e primeira coluna da imagem e da matriz de labels. Isso porque
	// a análise utiliza-se os 8 vizinhos de um pixel, e por este fato começa-se pela 2 linha 2 coluna
	for (i = 0; i < img->height; i++){
		data[(i)*step+(0)*channel] = 0;
		matrixLabel[i][0] = 0;
	}
	for (j = 0; j < img->width; j++){
		data[(0)*step+(j)*channel] = 0;
		matrixLabel[0][j] = 0;
	}
	
	int pixel;											// pixel atual
	
	unsigned int p11,p12,p13,p21;						// os 4 vizinhos ja analizados
														// __________________
														// p11 | p12   | p13
														// p21 | pixel | 
														//-------------------
	// Análise dos componentes conectados
	for (i = 1; i < img->height-1; i++) {
		for (j = 1; j < img->width-1; j++) {
			p11 = matrixLabel[i-1][j-1];
			p12 = matrixLabel[i-1][j];
			p13 = matrixLabel[i-1][j+1];
			p21 = matrixLabel[i][j-1];
			
			pixel = data[(i)*step+(j)*channel];
			
			if(pixel != 0){
				if(p11 != 0){
					if(p13 != 0 && p13 != p11){
						int x = matrixColor[p13];
						long size = 0;
						for(int h=0; h<=label; h++){
							if(matrixColor[h] == x && h != p11){
								matrixColor[h] = matrixColor[p11];
							}
						}
					}
					matrixLabel[i][j] = p11;
					matrixSize[p11]++;
					matrixRect[p11] = addPointToRect(j, i, matrixRect[p11]);
				}else{
					if(p12 != 0){
						matrixLabel[i][j] = p12;
						matrixSize[p12]++;
						matrixRect[p12] = addPointToRect(j, i, matrixRect[p12]);
					}else{
						if(p13 != 0){
							if(p21 != 0 && p21 != p13){
								int x = matrixColor[p21]; 
								for(int h=0; h<=label; h++){
									if(matrixColor[h] == x && h != p13){
										matrixColor[h] = matrixColor[p13];
									}
								}
							}
							matrixLabel[i][j] = p13;
							matrixSize[p13]++;
							matrixRect[p13] = addPointToRect(j, i, matrixRect[p13]);
						}else{
							if(p21 != 0){
								matrixLabel[i][j] = p21;
								matrixSize[p21]++;
								matrixRect[p21] = addPointToRect(j, i, matrixRect[p21]);
							}else{
								label++;
								matrixLabel[i][j] = label;
								color++;
								matrixColor[label] = color;
								matrixSize[label] = 1;
								matrixRect[label] = createRect(j, i, j, i);
							}
						}
					}
				}
			}else{
				matrixLabel[i][j] = 0;
			}
			
		}
	}
	
	
	ComponentList list = NULL;
	Component* component;
	
	// juntar labels de mesma cor
	for(i=1; i<=label; i++){
		component = getComponent(list, matrixColor[i]);
		if(component == NULL){
			// componente novo
			addComponent(&list, matrixColor[i], matrixSize[i], matrixRect[i]);
		}else{
			// componente já existente
			component->area += matrixSize[i];
			component->rect = joinRects(component->rect, matrixRect[i]);
		}
	}
	
	return list;
	
}

Component* newComponent(){
	Component* component;
	component = (Component *)malloc(sizeof(Component));
	return component;
}

void addComponent(ComponentList* list, int color, long area, Rect rect){
	Component* c = newComponent();
	c->color = color;
	c->area = area;
	c->rect = rect;
	c->next = NULL;
	if(*list != NULL){
		Component* component = *list;
		while(component->next != NULL){
			component = component->next;
		}
		component->next = c;
	}else{
		*list = c;
	}
}

Component* getComponent(ComponentList list, int color){
	if(list != NULL){
		Component* component = list;
		while(component->color != color){
			component = component->next;
			if(component == NULL){
				break;
			}
		}
		return component;
	}
	return NULL;
}

void removeAllComponents(ComponentList* list){
	Component* component;
	while(*list != NULL){
		component = *list;
		*list = component->next;
		free(component);
	}
}

Rect createRect(int x1, int y1, int x2, int y2){
	Rect r;
	CvPoint p1;
	CvPoint p2;
	
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
	
	r.min = p1;
	r.max = p2;
	
	return r;
}

Rect addPointToRect(int x, int y, Rect rect){
	if(x < rect.min.x)
		rect.min.x = x;
	if(y > rect.max.y)
		rect.max.y = y;
	if(x > rect.max.x)
		rect.max.x = x;
	
	return rect;
}

Rect joinRects(Rect r1, Rect r2){
	Rect rect;
	if(r1.min.x < r2.min.x){
		rect.min.x = r1.min.x;
	}else{
		rect.min.x = r2.min.x;
	}
	if(r1.min.y < r2.min.y){
		rect.min.y = r1.min.y;
	}else{
		rect.min.y = r2.min.y;
	}
	
	if(r1.max.x > r2.max.x){
		rect.max.x = r1.max.x;
	}else{
		rect.max.x = r2.max.x;
	}
	if(r1.max.y > r2.max.y){
		rect.max.y = r1.max.y;
	}else{
		rect.max.y = r2.max.y;
	}
	
	return rect;
}

#include "ConnectedComponent.h"

ComponentList getConnectedComponents(IplImage* img){
	// TODO: Melhorar matrixColor, pois é um vetor muito grande
	//		 Melhorar a alteração dos labels, for muito grande
	//		 Retornar posição de cada compoente
	//		Comentar o código
	
	int i, j;											// contadores para o for
	
	unsigned int matrixLabel[img->height][img->width]; 	// matriz do mesmo tamanho da imagem img
														// contendo os labels de cada pixel
														
	unsigned int matrixColor[INTLEN];					// matriz contendo a cor de cada label,
														// sendo matrixColor[label] = cor
														
	unsigned long matrixSize[INTLEN];					// matriz contendo a quantidade de pixel
														// de cada label, sendo matrixSize[label] = cor
														
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
						for(int h=0; h<INTLEN; h++){
							if(matrixColor[h] == x && h != p11){
								matrixColor[h] = matrixColor[p11];
							}
						}
					}
					matrixLabel[i][j] = p11;
					matrixSize[p11]++;
				}else{
					if(p12 != 0){
						matrixLabel[i][j] = p12;
						matrixSize[p12]++;
					}else{
						if(p13 != 0){
							if(p21 != 0 && p21 != p13){
								int x = matrixColor[p21]; 
								for(int h=0; h<INTLEN; h++){
									if(matrixColor[h] == x && h != p13){
										matrixColor[h] = matrixColor[p13];
									}
								}
							}
							matrixLabel[i][j] = p13;
							matrixSize[p13]++;
						}else{
							if(p21 != 0){
								matrixLabel[i][j] = p21;
								matrixSize[p21]++;
							}else{
								label++;
								matrixLabel[i][j] = label;
								color++;
								matrixColor[label] = color;
								matrixSize[label] = 1;
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
	
	for(i=1; i<INTLEN; i++){
		if(matrixColor[i] == 0)
			break;
		component = getComponent(list, matrixColor[i]);
		if(component == NULL){
			addComponent(&list, matrixColor[i], matrixSize[i]);
		}else{
			component->area += matrixSize[i];
		}
	}
	
	/*for (i = 1; i < img->height-1; i++) {
		for (j = 1; j < img->width-1; j++) {
			if(matrixColor[matrixLabel[i][j]] == 1){
				data[(i)*step+(j)*channel] = 255;
			}
			
			if(matrixColor[matrixLabel[i][j]] == 2){
				data[(i)*step+(j)*channel] = 120;
			}
			
			if(matrixColor[matrixLabel[i][j]] == 32){
				data[(i)*step+(j)*channel] = 50;
			}
		}
	}*/
	
	/*for(i =0; i< 50; i++){
		printf("%d - (%d, %d) (%d, %d)\n", i, matrixColor[i], matrixRect[i].min.x, matrixRect[i].min.y, 
		matrixRect[i].max.x, matrixRect[i].max.y);
	}*/
	
	/*printf("\nComponentes:\n");
	component = list;
	while(component != NULL){
		printf("%d\t%d\n", component->color, component->area);
		component = component->next;
	}
	
	cvNamedWindow( "teste", 1 );
	cvShowImage( "teste", img );
	
	cvWaitKey(0);*/
	
	return list;
	
}

Component* newComponent(){
	Component* component;
	component = (Component *)malloc(sizeof(Component));
	return component;
}

void addComponent(ComponentList* list, int color, long area){
	Component* c = newComponent();
	c->color = color;
	c->area = area;
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

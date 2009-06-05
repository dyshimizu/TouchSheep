#include <stdio.h>

#include "driver/ConnectedComponent.h"

int main(){
	
	printf("Testes...\n");
	IplImage* img = 0;
	IplImage* imggray = 0;
	img=cvLoadImage("imagem.bmp");
	imggray = cvCreateImage( cvGetSize(img), 8, 1 );
	cvCvtColor(img, imggray, CV_BGR2GRAY);
	getConnectedComponents(imggray);
}

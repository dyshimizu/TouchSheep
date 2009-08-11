#include "TSVideoDisplay.h"

#include <QImage>
#include <QPixmap>
#include <QPainter>

void TSVideoDisplay::setTSImage(TSImage *tsImg){
	QImage *qImage = new QImage( (unsigned char *)tsImg->imageData, tsImg->width, tsImg->height, 
								 tsImg->widthStep, QImage::Format_RGB888); 
							
	QPainter p(qImage);
	p.drawRect(300,220,40,40);
	
	QPixmap pm = QPixmap::fromImage(*qImage,0);
	
	setPixmap(pm);
}

void TSVideoDisplay::showFrame(TSImage *img){
	setTSImage(img);
}

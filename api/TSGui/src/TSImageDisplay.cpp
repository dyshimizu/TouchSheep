#include "TSImageDisplay.h"

#include <QLabel>
#include <QImage>
#include <QPixmap>

void TSImageDisplay::setTSImage(TSImage *tsImg){
	QImage qImage = QImage( (unsigned char *)tsImg->imageData, tsImg->width, tsImg->height, 
							tsImg->widthStep, QImage::Format_RGB888); 
	QPixmap pm = QPixmap::fromImage(qImage,0);
	
	setPixmap(pm);
}
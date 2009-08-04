#include "TSListenerGallery.h"

void TSListenerGallery::performed (TSEvent* e){
	emit newFrame(e->img);
}
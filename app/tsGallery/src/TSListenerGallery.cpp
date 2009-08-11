#include "TSListenerGallery.h"

void TSListenerGallery::performed (TSEvent* e){
	emit newFrame(e->img);
	
	std::list<TSMarker*>::iterator it;
	for ( it=e->tsMarkerList.begin() ; it != e->tsMarkerList.end(); it++ ){
		printf("(%d, %d)\n", (*it)->position.x, (*it)->position.y);
	}
}
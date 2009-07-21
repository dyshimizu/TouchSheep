#include "TSCore/TouchSheep.h"
#include "TSCore/TSTouchMarkerListener.h"

#include <exception>
using namespace std;

#include "stdio.h"

bool ok;
TouchSheep* app;

class Teste: public TSTouchMarkerListener{
	
public:
	Teste(int marker1, int marker2): TSTouchMarkerListener (marker1, marker2){
		
	}
	
	void touchPerformed(TSTouchMarkerEvent* e){
		printf("toquei!\n");
	}
	
	void releasePerformed(TSTouchMarkerEvent* e){
		printf("soltei!\n");
	}
	
	void distancePerformed (TSTouchMarkerEvent* e){
		if(!ok){
			app->addTSMarker(335, 76, 369, 97, 1);
			app->addTSMarker(326, 368, 389, 410, 2);
			ok = true;
		}
	}
	
};

int main(){
	ok = false;
	
	try{
		app = new TouchSheep("video.mpg", 30, 10, 256, 30);
		
		TSListener* l;
		l = new Teste(0,1);

		app->addTSListener(l);

		int i;
		i = app->start();

		printf("%d", i);
		scanf("%d",&i);
	}catch(exception& e){
		printf("%s\n", e.what());
	}
}

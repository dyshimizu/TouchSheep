#include "TSDisplay.h"

#include <highgui.h>

void fon_mouse( int event, int x, int y, int flags, void* param );
TSDisplay *TSDISPLAYTOCALLBACK;

TSDisplay::TSDisplay (char* name){
	
	TSDISPLAYTOCALLBACK = this;
	
	cvNamedWindow(name);
	cvSetMouseCallback(name, fon_mouse, 0);
}

TSDisplay::~TSDisplay (){
	
}

void TSDisplay::on_mouse( int event, int x, int y, int flags, void* param ){
	
}

void fon_mouse( int event, int x, int y, int flags, void* param ){
	TSDISPLAYTOCALLBACK->on_mouse(event, x, y, flags, param);
}
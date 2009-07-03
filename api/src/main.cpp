#include "TSApplication.h"

int main(){
	//CvCapture *cam = cvCaptureFromCAM(0);
	CvCapture *cam = cvCreateFileCapture("video.mpg");
	if(!cam)
		return 0;
	TSApplication* app;
	app = new TSApplication(cam, 30, 10, 256, 30);
	int i;
	i = app->start();
	printf("%d", i);
	scanf("%d",&i);
}

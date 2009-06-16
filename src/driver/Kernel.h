//
// Kernel.h
//
// Ígor Bonadio & Daniel Yutaka Shimizu
// 2009
//

#ifndef KERNEL_H
#define KERNEL_H

#include "cv.h"
#include "highgui.h"

#include "Camshift.h"

void kernelLoop(int cam, void handle(IplImage*, MarkerList), int refresh, int vmin, int vmax, int smin);
void kernelLoop(int cam, void handle(IplImage*, MarkerList), int refresh = 30, int vmin = 10, int vmax = 256, int smin = 30);

void addMarker(CvRect position, CvHistogram* hist);

#endif

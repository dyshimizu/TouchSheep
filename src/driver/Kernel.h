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

void kernelLoop(int cam, int vmin, int vmax, int smin);
void kernelLoop(int cam, int vmin = 10, int vmax = 256, int smin = 30);

#endif

#include "Camshift.h"

CvHistogram* getHistogram(IplImage* frame, IplImage* mask, CvRect selection){
	
	int hdims = 16;
	float hranges_arr[] = {0,180};
	float* hranges = hranges_arr;
	
	CvHistogram *hist = 0;
	hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );
		
	float max_val = 0.f;
	cvSetImageROI( frame, selection );
	cvSetImageROI( mask, selection );
	cvCalcHist( &frame, hist, 0, mask );
	cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 );
	cvConvertScale( hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0 );
	cvResetImageROI( frame );
	cvResetImageROI( mask );
	
	return hist;
}

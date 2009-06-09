#include "Camshift.h"

CvRect camshift(IplImage* frame, IplImage* mask, CvRect selection, CvHistogram* hist, CvBox2D *track_box){
	
	CvConnectedComp track_comp;
	
	IplImage* backproject;
	backproject = cvCreateImage( cvGetSize(frame), 8, 1 );
	cvCalcBackProject( &frame, backproject, hist );
	cvAnd( backproject, mask, backproject, 0 );
	
	cvCamShift( backproject, selection, cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ), &track_comp, track_box );
	
	return track_comp.rect;
}

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

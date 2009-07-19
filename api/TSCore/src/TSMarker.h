#ifndef TSMARKER_H
#define TSMARKER_H

class TSMarker {
public:
	int id;
	
	int markerType;
	
	struct {
		int x;
		int y;
		int width;
		int height;
	} position;
	
	struct {
		struct{
			float x;
			float y;
		} center;
		struct {
			float width;
			float height;
		} size;
		
		float angle;
	} track_box;
};

#endif

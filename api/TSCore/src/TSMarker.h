// This file is part of TouchSheep.
// 
//     TouchSheep is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     TouchSheep is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with TouchSheep.  If not, see <http://www.gnu.org/licenses/>.

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

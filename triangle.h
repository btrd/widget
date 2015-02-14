#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

typedef struct {
	float x;	
	float y;	
} point;

class Triangle {
  public:
  	point p1;
  	point p2;
  	point p3;

  	wxColour colour;

  	float thickness;
};

#endif
/* Star.h */
#ifndef Star_H
#define Star_H
#include "STD_H.h"
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Star : public Shape
{
	//friend ostream& operator<<(ostream &, PolyGonle &);
public:
	Star();
	Star(string name);
	Star(int px, int py, int radius, int num_vertices, double ang, COLORREF ln_clr,	COLORREF br_clr, int pen_thick, string name);
	//PolyGonle(PolyGonle &pg);
	~Star();
	//double getArea();
	virtual void draw(ConsolePixelFrame cp_frame);
	virtual void draw(); // // used for testing of late binding
	void fprint(ostream&);
	int getRadius() { return radius; }
	int getNumPoly() { return num_vertices; }
	Star& operator=(Star& pg);
protected:
	int radius;
	int num_vertices;
};
#endif
/** Polygon.h */
#ifndef PolyGon_H
#define PolyGon_H
#include "STD_H.h"
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class PolyGon : public Shape
{
	//friend ostream& operator<<(ostream &, PolyGonle &);
public:
	PolyGon();
	PolyGon(string name);
	PolyGon(int px, int py, int radius, int num_poly, double ang, COLORREF ln_clr, COLORREF br_clr,	int pen_thick, string name);
	~PolyGon();
	virtual void draw(ConsolePixelFrame cp_frame);
	void fprint(ostream&);
	int getRadius() { return radius; }
	int getNumPoly() { return num_poly; }
	PolyGon& operator=(PolyGon& pg);
protected:
	int radius;
	int num_poly;
};
#endif
/*Circle.h*/
#ifndef Circle_H
#define Circle_H
#include "STD_H.h"
#include "Shape.h"
using namespace std;
#define PI 3.14159
class Circle : public Shape
{
	friend ostream& operator<<(ostream&, Circle&);
public:
	Circle();
	Circle(string name);
	Circle(int px, int py, int r, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	//Circle(Circle &tr);
	~Circle();
	double getArea();
	virtual void draw(ConsolePixelFrame cp_frame);
	void fprint(ostream&);
	int getRadius() const { return radius; }
	void setRadius(int r) { radius = r; }
	Circle& operator=(const Circle& cir);
protected:
	int radius;
};
#endif
/* Shape.h */
#ifndef SHAPE_H
#define SHAPE_H
#include "STD_H.h"
#include "ConsolePixelDrawing.h"
#include "Color.h"
using namespace std;
#define PI 3.14159
class ConsolePixelFrame;
class Shape
{
	//friend ostream& operator<<(ostream&, Shape&);
public:
	Shape(); // default constructor
	Shape(string name);
	Shape(int px, int py, int angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // constructor
	virtual ~Shape();
	virtual void draw(ConsolePixelFrame cp_frame); // device context of console
	virtual void draw(); // used for testing of late binding
	void fprint(ostream&);
	int get_px() const { return px; }
	int get_py() const { return py; }
	void set_px(int x) { px = x; }
	void set_py(int y) { py = y; }
	string getName() { return name; }
	void setName(string n) { name = n; }
	Shape& operator=(const Shape& s);
protected:
	int px; // position x
	int py; // position y
	int angle; // angle in degree
	string name;
	int pen_thickness;
	COLORREF line_color;
	COLORREF brush_color;
};
#endif
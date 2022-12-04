/*Shape.cpp*/
#include "Shape.h"
Shape::Shape()					// default constructor
	:px(0.0), py(0.0), angle(0), name(""), pen_thickness(0), line_color(000000), brush_color(000000)
{

}

Shape::Shape(string nm)			// constructor
	:px(0.0), py(0.0), angle(0), pen_thickness(0), line_color(000000), brush_color(000000)
{
	name = nm;
}

Shape::Shape(int pos_x, int pos_y, int ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string nm)		// constructor
{
	px = pos_x;
	py = pos_y;
	angle = ang;
	line_color = ln_clr;
	brush_color = br_clr;
	pen_thickness = pen_thick;
	name = nm;
}

void Shape::fprint(ostream& fout)			// printout
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << ")";
}

Shape& Shape::operator=(const Shape& s)			// operation overloading
{
	this->px = s.px;
	this->py = s.py;
	this->angle = s.angle;
	this->line_color = s.line_color;
	this->brush_color = s.brush_color;
	this->pen_thickness = s.pen_thickness;
	this->name = s.name;
	return *this;
}

Shape::~Shape()		// destructor
{

}

void Shape::draw()
{
	cout << "draw() of " << name << endl;
}

void Shape::draw(ConsolePixelFrame cp_frame)		// late binding
{

}
/*Circle.cpp*/
#include "Circle.h"

ostream& operator<<(ostream& fout, Circle& cir)			// operation overloading
{
	cir.fprint(fout);
	return fout;
}

Circle::Circle()					// default constructor
	:Shape()
{
	radius = 0;
}

Circle::Circle(string name)			// constructor
	:Shape(name)
{
	radius = 0;
}

Circle::Circle(int px, int py, int r, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)		// constructor
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
}

Circle::~Circle()					// deconstructor
{

}

double Circle::getArea()			// calculate Area
{
	double area = 0.0;
	area = PI * radius * radius;
	return area;
}

void Circle::fprint(ostream& fout)		// printout
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << "), " << "radius : (" << radius << ")";
}

Circle& Circle::operator=(const Circle& cir)			// operation overloading
{
	this->Shape::operator=(cir);
	this->radius = cir.radius;
	return* this;
}

void Circle::draw(ConsolePixelFrame cp_frame)			// late binding
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int pos_center_x, pos_center_y;

	pos_center_x = cp_frame.get_cpfr_px() + get_px();		// center x
	pos_center_y = cp_frame.get_cpfr_py() + get_py();		// center y

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);		// create pen
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Ellipse(hdc, pos_center_x - radius, pos_center_y - radius, pos_center_x + radius, pos_center_y + radius);		// draw
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}
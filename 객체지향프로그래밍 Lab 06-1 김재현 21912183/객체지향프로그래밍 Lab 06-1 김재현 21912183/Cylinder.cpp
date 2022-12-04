/*Cylinder.cpp*/
#include "Cylinder.h"

ostream& operator<<(ostream& fout, const Cylinder& Cldr)		// operation overloading <<
{
	Cldr.fprint(fout);
	return fout;				// chained operating
}

Cylinder::Cylinder()						// default constructor
	:Shape()
{
	radius = 0;
	height = 0;
}

Cylinder::Cylinder(string nm)				// constructor
	:Shape(name)
{
	radius = 0;
	height = 0;
}

Cylinder::Cylinder(int px, int py, int r, int ang, int hgt, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)		// constructor
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
	height = hgt;
}

Cylinder::~Cylinder()						// destructor
{

}

double Cylinder::getArea()				// calculate area
{
	double area = 0.0;
	area = PI * radius * radius;
	return area;
}

void Cylinder::fprint(ostream& fout) const		// print out
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << "), " << "radius : (" << radius << "), height : (" << height << ")";
}

Cylinder& Cylinder::operator=(const Cylinder& cir)			// operation overloading = assign
{
	this->Shape::operator=(cir);
	this->radius = cir.radius;
	this->height = cir.height;
	return *this;
}

void Cylinder::draw()					// late binding
{
	cout << "draw() of Cylinder";
	fprint(cout);
}

void Cylinder::draw(ConsolePixelFrame cp_frame)			// late binding draw
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);			// create pen
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	int cx = cp_frame.get_cpfr_px() + get_px();			// center x
	int cy = cp_frame.get_cpfr_py() + get_py();			// center y

	MoveToEx(hdc, cx - radius, cy - height / 2, (LPPOINT)NULL);
	LineTo(hdc, cx - radius, cy + height / 2);
	MoveToEx(hdc, cx + radius, cy - height / 2, (LPPOINT)NULL);
	LineTo(hdc, cx + radius, cy + height / 2);
	Ellipse(hdc, cx - radius, cy - height / 2 - 20, cx + radius, cy - height / 2 + 20);
	MoveToEx(hdc, cx - radius, cy + height / 2, (LPPOINT)NULL);
	ArcTo(hdc, cx - radius, cy + height / 2 - 20, cx + radius, cy + height / 2 + 20, cx - radius, cy + height / 2, cx + radius, cy + height / 2);
	SelectObject(hdc, old_pen); DeleteObject(new_pen);
	SelectObject(hdc, old_brush); DeleteObject(new_brush);
}
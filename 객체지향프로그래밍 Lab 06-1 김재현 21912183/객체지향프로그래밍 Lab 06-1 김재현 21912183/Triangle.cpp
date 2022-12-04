/*Triangle.cpp*/
#include "Triangle.h"
Triangle::Triangle()							// default constructor
	:Shape()
{
	base = 0;
	tri_height = 0;
}

Triangle::Triangle(string name)					// constructor
	:Shape(name)
{
	base = 0;
	tri_height = 0;
}

Triangle::Triangle(int px, int py, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)		// constructor
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	base = b;
	tri_height = h;
}

Triangle::~Triangle()							// destructor
{

}

double Triangle::getArea()						// calculate area
{
	double area = 0.0;
	area = base * tri_height / 2;
	return area;
}

void Triangle::fprint(ostream& fout)			// printout
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << "), " << "base : (" << base << "), tri_height : (" << tri_height << ")";
}

Triangle& Triangle::operator=(const Triangle& tri)			// operation overloading =
{
	this->Shape::operator=(tri);
	this->base = tri.base;
	this->tri_height = tri.tri_height;
	return *this;
}

void Triangle::draw(ConsolePixelFrame cp_frame)				// draw
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_cpfr_px() + get_px();		// center x
	pos_center_y = cp_frame.get_cpfr_py() + get_py();		// center y

	// °¢ ²ÀÁþÁ¡ÀÇ position
	POINT p[3];
	p[0].x = pos_center_x - base / 2;
	p[0].y = pos_center_y + tri_height * 1.0 / 2.0;
	p[1].x = pos_center_x + base / 2;
	p[1].y = pos_center_y + tri_height * 1.0 / 2.0;
	p[2].x = pos_center_x;
	p[2].y = pos_center_y - tri_height * 1.0 / 2.0;

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);		// create pen
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, p, 3);						// draw
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}
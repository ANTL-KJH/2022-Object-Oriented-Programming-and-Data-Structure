/*Rectang.cpp*/
#include "Rectang.h"

Rectang::Rectang()							// default constructor
	:Shape()
{
	width = 0;
	length = 0;
}
Rectang::Rectang(string name)				// constructor
	:Shape(name)
{

}

Rectang::Rectang(int px, int py, int w, int l, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)			// constructor
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	width = w;
	length = l;
}

Rectang::~Rectang()							// destructor
{

}

double Rectang::getArea()					// calculate area
{
	double area = 0.0;
	area = width * length;
	return area;
}

Rectang& Rectang::operator=(Rectang& rec)		// operation overloading = assign
{
	this->Shape::operator=(rec);
	this->width = rec.width;
	this->length = rec.length;
	return *this;
}

void Rectang::fprint(ostream& fout)				// printout
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << "), " << "width : (" << width << "), length : (" << length << ")";
}

void Rectang::draw(ConsolePixelFrame cp_frame)					// draw
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_cpfr_px() + get_px();
	pos_center_y = cp_frame.get_cpfr_py() + get_py();
	// 각 모서리의 position
	POINT p[4];
	p[0].x = pos_center_x - width / 2;
	p[0].y = pos_center_y - length / 2;
	p[1].x = pos_center_x + width / 2;
	p[1].y = pos_center_y - length / 2.0;
	p[2].x = pos_center_x + width / 2;
	p[2].y = pos_center_y + length / 2.0;
	p[3].x = pos_center_x - width / 2;
	p[3].y = pos_center_y + length / 2.0;

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);		// create pen
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, p, 4);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}


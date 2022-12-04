/*PolyGon.cpp*/
#include "PolyGon.h"
PolyGon::PolyGon()							// default constructor
	:Shape()
{
	radius = 0;
	num_poly = 0;
}

PolyGon::PolyGon(string name)				// constructor
	:Shape(name)
{
	radius = 0;
	num_poly = 0;
}

PolyGon::PolyGon(int px, int py, int rad, int n_poly, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)		// constructor
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = rad;
	num_poly = n_poly;
}

PolyGon::~PolyGon()							// destructor
{

}

void PolyGon::fprint(ostream& fout)
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << "), " << "radius : (" << radius << "), num_poly : (" << num_poly << ")";
}

PolyGon& PolyGon::operator=(PolyGon& pg)				// operation overloading = assisgn
{
	this->Shape::operator=(pg);
	this->radius = pg.radius;
	this->num_poly = pg.num_poly;
	return *this;
}

void PolyGon::draw(ConsolePixelFrame cp_frame)			// late binding draw
{
	POINT* points = (POINT*)malloc(num_poly * sizeof(POINT));
	double rad_angle, delta_angle;
	int pos_center_x, pos_center_y;
	int x, y;
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	hdc = cp_frame.getConsole_DC();

	pos_center_x = cp_frame.get_cpfr_px() + get_px();		// center x
	pos_center_y = cp_frame.get_cpfr_py() + get_py();		// center y
	delta_angle = 2.0 * PI / num_poly;
	rad_angle = PI / 2.0;

	for (int i = 0; i < num_poly; i++, rad_angle += delta_angle)
	{
		x = pos_center_x + radius * cos(rad_angle);
		y = pos_center_y - radius * sin(rad_angle);
		points[i].x = x;
		points[i].y = y;
	}

	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);		// create pen
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Polygon(hdc, points, num_poly);				// draw Polygon

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}
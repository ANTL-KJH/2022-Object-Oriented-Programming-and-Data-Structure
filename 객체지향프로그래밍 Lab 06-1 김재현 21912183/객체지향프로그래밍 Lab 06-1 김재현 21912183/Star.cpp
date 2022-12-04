/*Star.cpp*/
#include "Star.h"

Star::Star()								// default constructor
	:Shape()
{
	radius = 0;
	num_vertices = 0;
}

Star::Star(string name)						// constructor
	:Shape(name)
{
	radius = 0;
	num_vertices = 0;
}

Star::Star(int px, int py, int rad, int n_vertices, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = rad;
	num_vertices = n_vertices;
}

Star::~Star()								// destructor
{

}

Star& Star::operator=(Star& pg)				// operation overloading = assign
{
	this->Shape::operator=(pg);
	this->radius = pg.radius;
	this->num_vertices = pg.num_vertices;
	return *this;
}

void Star::fprint(ostream& fout)			// printout
{
	fout << "name : " << name << "pos : (" << px << ", " << py << ")" << "angle : (" << angle << "), \nline_color : ("
		<< line_color << "), brush_color : (" << brush_color << "), pen_thickness : (" << pen_thickness << "), " << "radius : (" << radius << "), num_vertices : (" << num_vertices << ")";
}

void Star::draw(ConsolePixelFrame cp_frame)			// late binding draw
{
	POINT* points = (POINT*)malloc(5.0 * sizeof(POINT));
	double rad_angle, delta_angle;
	int pos_center_x, pos_center_y;
	int x, y;
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	hdc = cp_frame.getConsole_DC();

	pos_center_x = cp_frame.get_cpfr_px() + get_px();		// center x
	pos_center_y = cp_frame.get_cpfr_py() + get_py();		// center y
	delta_angle = 2.0 * PI / 5.0;
	rad_angle = PI / 2.0;

	for (int i = 0; i < 5.0; i++, rad_angle += delta_angle)
	{
		x = pos_center_x + radius * cos(rad_angle);
		y = pos_center_y - radius * sin(rad_angle);
		points[i].x = x;
		points[i].y = y;
	}

	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);			// create pen
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);


	MoveToEx(hdc, points[0].x, points[0].y, NULL);				// Start는 각 점을 Line으로 연결해야함
	LineTo(hdc, points[2].x, points[2].y);
	LineTo(hdc, points[4].x, points[4].y);
	LineTo(hdc, points[1].x, points[1].y);
	LineTo(hdc, points[3].x, points[3].y);
	LineTo(hdc, points[0].x, points[0].y);

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Star::draw()			// late binding
{
	cout << "draw Star";
}
/*AngleArc.cpp*/
#include "AngledArc.h"
#include "ConsolePixelDrawing.h"

AngledArc::AngledArc()						// default constructor
	:Shape("no_name"), radius(0), start_angle(0), sweep_angle(0)
{

}

AngledArc::AngledArc(string name)			// constructor
	: Shape(name), radius(0), start_angle(0), sweep_angle(0)
{
	
}

AngledArc::AngledArc(int px, int py, int r, int ang, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)		// constructor
	: Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
	start_angle = start_ang;
	sweep_angle = sweep_ang;
}

AngledArc::~AngledArc()						// destructor
{

}

void AngledArc::draw()						// late binding
{
	cout << "draw() of AngleArc";
	fprint(cout);
}

void AngledArc::draw(ConsolePixelFrame cp_frame)		// draw late binding
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int start_px, start_py;
	double start_ang_rad;

	int fr_px = cp_frame.get_cpfr_px() + get_px();		// frame x
	int fr_py = cp_frame.get_cpfr_py() + get_py();		// frame y

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);	// pen »ý¼º
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	start_ang_rad = start_angle * 3.141592 / 180.0;				// start angle transform to radian 

	start_px = fr_px + radius * cos(start_ang_rad);		// start px
	start_py = fr_py - radius * sin(start_ang_rad);		// start py

	MoveToEx(hdc, fr_px, fr_py, (LPPOINT)NULL);
	LineTo(hdc, start_px, start_py);
	AngleArc(hdc, fr_px, fr_py, radius, start_angle, sweep_angle);
	LineTo(hdc, fr_px, fr_py);
	SelectObject(hdc, old_pen); DeleteObject(new_pen);
	SelectObject(hdc, old_brush); DeleteObject(new_brush);
}

ostream& operator<<(ostream& fout, const AngledArc& ang_arc)		// operation overloading << 
{
	fout << ang_arc.name << ": pos(" << ang_arc.get_px() << ", " << ang_arc.get_py() << ")";
	fout << ", line_color("; fprintRGB(fout, ang_arc.line_color);
	fout << "), brush_color("; fprintRGB(fout, ang_arc.brush_color);
	fout << ")";
	fout << ", radius(" << ang_arc.radius << ")";
	fout << ", start_ang (" << ang_arc.start_angle << "), sweep_ang(" << ang_arc.sweep_angle << ")";
	fout << endl;
	return fout;		// chained operation
}

AngledArc& AngledArc::operator=(const AngledArc& right)			// operation overloading = 
{
	Shape::operator=(right);
	radius = right.radius;
	return *this;
}

void AngledArc::fprint(ostream& fout)							// printout
{
	Shape::fprint(fout);
	fout << ", radius (" << radius << "), start_angle (" << start_angle;
	fout << "), sweep_angle (" << sweep_angle << ")";
	fout << endl;
}

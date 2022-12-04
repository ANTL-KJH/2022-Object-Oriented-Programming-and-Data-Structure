/* AngleArc.h */

#ifndef ANGLE_ARC_H
#define ANGLE_ARC_H
#include "STD_H.h"
#include "Shape.h"
using namespace std;
class AngledArc : public Shape
{
	friend ostream& operator<<(ostream&, const AngledArc&);
public:
	AngledArc();
	AngledArc(string name);
	AngledArc(int px, int py, int r, int ang, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	//AngledArc(AngledArc &angarc);
	~AngledArc();
	virtual void draw(ConsolePixelFrame cp_frame);
	virtual void draw(); // // used for testing of late binding
	void fprint(ostream&);
	int getRadius() const { return radius; }
	void setRadius(int r) { radius = r; }
	AngledArc& operator=(const AngledArc& cir);
protected:
	int radius;
	int start_angle;
	int sweep_angle;
};
#endif
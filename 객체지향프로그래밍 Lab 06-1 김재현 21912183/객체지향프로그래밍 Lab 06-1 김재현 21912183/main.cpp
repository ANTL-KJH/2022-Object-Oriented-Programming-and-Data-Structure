/*
* ������Ʈ�� : "��ü�������α׷��� Lab 06-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - Ŭ����, ������ �����ε�, ����� �̿��Ͽ� �л� �����͸� ó���ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.10.11
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����					����			��������
* JH KIM			2022.10.11			v1.0		���� �ۼ�
* JH KIM			2022.10.12			v1.1		AngledArc�ۼ�
* JH KIM			2022.10.13			v1.2		rec, cylinder constructor ���� ����
*/

#include "STD_H.h"
#include "ConsolePixelDrawing.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectang.h"
#include "Polygon.h"
#include "Star.h"
#include "AngledArc.h"
#include "Cylinder.h"


int main()
{
	int key;
	// class object gen
	Circle cir(100, 200, 80, 0, RGB_BLACK, RGB_RED, 3, "Circle");
	Triangle tri(300, 200, 150, 130, 0, RGB_BLACK, RGB_YELLOW, 3, "Triangle");
	Rectang rec(500, 200, 150, 150, 0, RGB_BLACK, RGB_BLUE, 4, "Rectangle");
	PolyGon poly_5(700, 200, 80, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Polygon_5");
	PolyGon poly_7(100, 400, 80, 7, 0, RGB_BLACK, RGB_MAGENTA, 4, "Polygon_7");
	Star star_5(300, 400, 80, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Star_5");
	AngledArc angle_arc(500, 400, 80, 0, 45, 270, RGB_RED, RGB_BLUE, 4, "Angle_Arc");
	Cylinder cyl(700, 400, 80, 0, 100, RGB_BLUE, RGB_WHITE, 4, "Cylinder");
	
	// frame
	ConsolePixelFrame frame(50,100);
	//system("mode con: lines=50 cols=150 | title ANTL");
	frame.addShape(&cir);
	frame.addShape(&tri);
	frame.addShape(&rec);
	frame.addShape(&poly_5);
	frame.addShape(&poly_7);
	frame.addShape(&star_5);
	frame.addShape(&angle_arc);
	frame.addShape(&cyl);

	frame.drawShapes();			// draw

	printf("hit any key to continue ....");
	key = _getch();
	return 0;
}
#pragma once
#include "glaux.h"
#include "glut.h"
#include "Point.h"

struct Rectangl
{
	Point LeftPoint;
	Point RightPoint;

	Rectangl(Point p1 = 0, Point p2 = 0)
	{
		LeftPoint = p1;
		RightPoint = p2;
	}

	void SetObgect(Point p1, Point p2)
	{
		LeftPoint = p1;
		RightPoint = p2;
	}

	void Draw(bool isflag = false)
	{
		glBegin(isflag ? GL_POLYGON : GL_LINE_LOOP);
		glVertex2d(LeftPoint.x, LeftPoint.y);
		glVertex2d(RightPoint.x, LeftPoint.y);
		glVertex2d(RightPoint.x, RightPoint.y);
		glVertex2d(LeftPoint.x, RightPoint.y);
		glEnd();
	}

	void Move(int delta = 0)
	{
		LeftPoint.x += delta;
		RightPoint.x += delta;
	}
};
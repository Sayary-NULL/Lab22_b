#pragma once
#include <math.h>
#include "glut.h"
#include "Point.h"

struct Circl
{
	Point Centr;
	int radius;
	bool isIntr = false;
	int Prise;

	Circl(Point c, int r, int p) : Centr(c), radius(r) 
	{
		if (p <= 30)
			Prise = -2;
		else if (p >= 90)
			Prise = 2;
		else Prise = 1;
	}
	
	void Draw(bool isdebuge = false, bool isHard = false)
	{
		int N = 360;
		glBegin(GL_TRIANGLE_FAN); // GL_LINE_LOOP
		for (int i = 1; i <= N; i++)
		{
			if (!isHard)
			{
				if (Prise == -2)
					glColor3f(1.0f, 0.0f, 0.0f);
				else if (Prise == 1)
					glColor3f(0.0f, 1.0f, 0.0f);
				else glColor3f(0.0f, 0.0f, 1.0f);
			}
			else
			{
				glColor3f(0.0f, 1.0f, 0.0f);
			}

			if (isdebuge && isIntr)
				glColor3f(0.0f, 1.0f, 1.0f);

			glVertex2f(Centr.x + radius * cos(2 * 3.14 / N * i), Centr.y + radius * sin(2 * 3.14 / N * i));
		}
		glEnd();

		if (isdebuge)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2d(Centr.x - radius, Centr.y - radius);
			glVertex2d(Centr.x + radius, Centr.y - radius);
			glVertex2d(Centr.x + radius, Centr.y + radius);
			glVertex2d(Centr.x - radius, Centr.y + radius);
			glEnd();
		}
	}
};
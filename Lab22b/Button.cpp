#include "Button.h"
#include <cstring>

void Button::TextXY(const char* text, int x, int y)
{
	glRasterPos2i(x, y); //позиция текста
	for (int i = 0; i < strlen(text); i++)
	{

		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

Button::Button()
{
	backback.SetObgect(0, 0);
	background.SetObgect(0, 0);
	front.SetObgect(0, 0);
}

Button::Button(Point center, int radiusW, int radiusH, int sizecircuit) : backback(Point(center.x - radiusW - 2 * sizecircuit, center.y - radiusH - 2 * sizecircuit), Point(center.x + radiusW + 2 * sizecircuit, center.y + radiusH + 2 * sizecircuit)),
																		background(Point(center.x - radiusW - sizecircuit, center.y - radiusH - sizecircuit), Point(center.x + radiusW + sizecircuit, center.y + radiusH + sizecircuit)),
																		front(Point(center.x - radiusW, center.y - radiusH), Point(center.x + radiusW, center.y + radiusH))
{
	Center = center;
	RadiusH = radiusH;
	RadiusW = radiusW;
}

void Button::Draw()
{
	if (isMouseInBotton)
	{
		glColor3f(BackR, BackG, BackB);
		backback.Draw(true);
	}

	glColor3f(BackR, BackG, BackB);
	background.Draw(true);
	glColor3f(FrontR, FrontG, FrontB);
	front.Draw(true);

	if (ButtonText != nullptr)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		TextXY(ButtonText, XText, YText);
	}
}

void Button::SetObject(Point center, int radiusW, int radiusH, int sizecircuit, void (*func)(), const char *text)
{
	backback.SetObgect(Point(center.x - radiusW - 2 * sizecircuit, center.y - radiusH - 2 * sizecircuit), Point(center.x + radiusW + 2 * sizecircuit, center.y + radiusH + 2 * sizecircuit));
	background.SetObgect(Point(center.x - radiusW - sizecircuit, center.y - radiusH - sizecircuit), Point(center.x + radiusW + sizecircuit, center.y + radiusH + sizecircuit));
	front.SetObgect(Point(center.x - radiusW, center.y - radiusH), Point(center.x + radiusW, center.y + radiusH));
	PresButtonFunc = func;
	ButtonText = text;
	Center = center;
	RadiusH = radiusH;
	RadiusW = radiusW;

	if (text != nullptr)
	{
		XText = Center.x - (strlen(text) * 9) / 2;
		YText = Center.y - 5;
	}
}

void Button::SetBack(GLfloat r, GLfloat g, GLfloat b)
{
	BackR = r;
	BackG = g;
	BackB = b;
}

void Button::SetFront(GLfloat r, GLfloat g, GLfloat b)
{
	FrontR = r;
	FrontG = g;
	FrontB = b;
}

bool Button::MouseInBotton(int x, int y)
{
	if (front.LeftPoint.x <= x && front.RightPoint.x >= x && front.RightPoint.y >= y && front.LeftPoint.y <= y)
		isMouseInBotton = true;
	else isMouseInBotton = false;
	return isMouseInBotton;
}

void Button::SetFunc(void(*func)())
{
	PresButtonFunc = func;
}

bool Button::PressBotton(int x, int y)
{
	MouseInBotton(x, y);

	if (PresButtonFunc != nullptr && isMouseInBotton)
	{
		PresButtonFunc();
		return true;
	}

	return false;
}

Button::~Button()
{
	PresButtonFunc = nullptr;
}

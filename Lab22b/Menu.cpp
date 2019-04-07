#include "Menu.h"

Menu::Menu()
{}

void Menu::TextXY(const char* text, int x, int y)
{
	glRasterPos2i(x, y); //позиция текста
	for (int i = 0; i < strlen(text); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void Menu::SetText(const char *text, GLfloat centrX, GLfloat centrY)
{
	XText = centrX - (strlen(text) * 9) / 2;
	YText = centrY - 5;
	MenuText = text;
}

void Menu::SetFon(Point center, int radiusW, int radiusH, int sizecircuit)
{
	Back.SetObgect(Point(center.x - radiusW - sizecircuit, center.y - radiusH - sizecircuit), Point(center.x + radiusW + sizecircuit, center.y + radiusH + sizecircuit));
	Front.SetObgect(Point(center.x - radiusW, center.y - radiusH), Point(center.x + radiusW, center.y + radiusH));
}

void Menu::AddButton(Button &b)
{
	Buttons.push_back(b);
}

void Menu::SetColorCircuit(GLfloat r, GLfloat g, GLfloat b)
{
	BackR = r;
	BackG = g;
	BackB = b;
}

void Menu::SetColorFon(GLfloat r, GLfloat g, GLfloat b)
{
	FrontR = r;
	FrontG = g;
	FrontB = b;
}

void Menu::MouseInButtins(int x, int y)
{
	for (int i = 0; i < Buttons.size(); i++)
		Buttons[i].MouseInBotton(x, y);
}

void Menu::MousePressButtons(int x, int y)
{
	for (int i = 0; i < Buttons.size(); i++)
		Buttons[i].PressBotton(x, y);
}

void Menu::Draw()
{
	glColor3f(BackR, BackG, BackB);
	Back.Draw(true);
	glColor3f(FrontR, FrontG, FrontB);
	Front.Draw(true);

	if (MenuText != nullptr)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		TextXY(MenuText, XText, YText);
	}

	for (int i = 0; i < Buttons.size(); i++)
		Buttons[i].Draw();
}

Menu::~Menu()
{}

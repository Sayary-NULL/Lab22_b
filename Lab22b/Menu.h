#pragma once
#include <vector>
#include "Button.h"

using namespace std;

class Menu
{
	Point Centr;
	int RediusW, RadiusH;
	int sizecircuit;
	Rectangl Back, Front;
	GLfloat BackR = 0.0f, BackG = 0.0f, BackB = 0.0f;
	GLfloat FrontR = 0.0f, FrontG = 0.0f, FrontB = 0.0f;
	vector<Button> Buttons;

	const char *MenuText = nullptr;
	GLfloat XText, YText;

private:
	void TextXY(const char* text, int x, int y);

public:
	Menu();
	void SetText(const char *text, GLfloat centrX, GLfloat centrY);
	void SetFon(Point center, int radiusW, int radiusH, int sizecircuit);
	void AddButton(Button &b);
	void SetColorCircuit(GLfloat r, GLfloat g, GLfloat b);
	void SetColorFon(GLfloat r, GLfloat g, GLfloat b);
	void MouseInButtins(int x, int y);
	void MousePressButtons(int x, int y);
	void Draw();
	~Menu();
};


#pragma once
#include "Rectangl.h"

class Button
{
	Point Center;
	int RadiusW, RadiusH;

	Rectangl background,
		front, backback;

	GLfloat BackR = 0.0f, BackG = 0.0f, BackB = 0.0f;
	GLfloat FrontR = 0.0f, FrontG = 0.0f, FrontB = 0.0f;

	bool isMouseInBotton = false;

	void (*PresButtonFunc)() = nullptr;

	const char *ButtonText = nullptr;
	GLfloat XText, YText;

private:
	void TextXY(const char* text, int x, int y);

public:
	Button();
	Button(Point center, int radiusW, int radiusH, int sizecircuit);
	void Draw();
	void SetObject(Point center, int radiusW, int radiusH, int sizecircuit, void(*func)() = nullptr, const char *text = nullptr);
	void SetBack(GLfloat r, GLfloat g, GLfloat b);
	void SetFront(GLfloat r, GLfloat g, GLfloat b);
	bool MouseInBotton(int x, int y);
	bool PressBotton(int x, int y);
	void SetFunc(void(*func)());
	~Button();
};


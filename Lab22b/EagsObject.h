#pragma once
#include "Rectangl.h"
#include "glaux.h"
#include "glut.h"

class EagsObject
{
	AUX_RGBImageRec* ReadEags = nullptr;
	AUX_RGBImageRec* BlueEags = nullptr;
	AUX_RGBImageRec* GrenEags = nullptr;
	Rectangl BackReck;
	GLfloat RadiusW = 0, RadiusH = 0;

public:
	int Prise = 0;

public:
	EagsObject();
	EagsObject(Point center, int prise, AUX_RGBImageRec* r, AUX_RGBImageRec* g, AUX_RGBImageRec* b);
	void SetObject(Point center, int prise, AUX_RGBImageRec* r, AUX_RGBImageRec* g, AUX_RGBImageRec* b);
	void SetImage(AUX_RGBImageRec* r, AUX_RGBImageRec* g, AUX_RGBImageRec* b);
	void MoveCircl(int delta);
	void Draw(bool isDebage = false);
	Point GetLeftPoint();
	Point GetRightPoint();
	~EagsObject();
};


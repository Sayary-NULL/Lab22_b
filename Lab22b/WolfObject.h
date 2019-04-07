#pragma once
#include "Rectangl.h"
#include "glut.h"
#include "glaux.h"

using namespace std;

class WolfObject
{
	Rectangl BackRect;
	int RadiusW = 0, RadiusH = 0;
	AUX_RGBImageRec* OImage = nullptr;
	AUX_RGBImageRec* OImageTransform = nullptr;

public:
	WolfObject();
	void SetObject(Rectangl p);
	void SetImage(AUX_RGBImageRec* p);
	void SetImageTransform(AUX_RGBImageRec* p);
	void SetNewCoord(int x, int y);
	Point GetLeftPoint();
	Point GetRightPoint();
	void Darw(bool param = false);
	~WolfObject();
};


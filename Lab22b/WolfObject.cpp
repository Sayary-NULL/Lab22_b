#include "WolfObject.h"



WolfObject::WolfObject()
{
}

void WolfObject::SetObject(Rectangl p)
{
	BackRect = p;
	RadiusW = (p.RightPoint.x - p.LeftPoint.x) / 2;
	RadiusH = (p.RightPoint.y - p.LeftPoint.y) / 2;
}

void WolfObject::SetImage(AUX_RGBImageRec* p)
{
	OImage = p;
}

void WolfObject::SetNewCoord(int x, int y)
{
	BackRect.LeftPoint.x = x - RadiusW ;
	BackRect.RightPoint.x = x + RadiusW;
}

Point WolfObject::GetLeftPoint()
{
	return BackRect.LeftPoint;
}

Point WolfObject::GetRightPoint()
{
	return BackRect.RightPoint;
}

void WolfObject::Darw()
{
	if (OImage != nullptr)
	{
		glRasterPos3d(BackRect.LeftPoint.x, BackRect.LeftPoint.y - OImage->sizeY + 3*RadiusH, 1); // ������ ����� ���� �����������
		glPixelZoom(1, 1); // ������������ ��������������� �� ������ � ������
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // ������ �������� ����������� � ������
		glDrawPixels(OImage->sizeX, OImage->sizeY, // ������ � ������ � ��������
			GL_RGB, // ������ ����� ��������
			GL_UNSIGNED_BYTE, // ������ �������� ���������
			OImage->data); // ������ �����������
	}

	//BackRect.Draw();
}



WolfObject::~WolfObject()
{
}

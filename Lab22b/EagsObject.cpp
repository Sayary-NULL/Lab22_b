#include "EagsObject.h"
#include <exception>

EagsObject::EagsObject()
{
}

EagsObject::EagsObject(Point center, int prise, AUX_RGBImageRec* r, AUX_RGBImageRec* g, AUX_RGBImageRec* b)
{
	SetObject(center, prise, r, g, b);
}

void EagsObject::SetObject(Point center, int prise, AUX_RGBImageRec* r, AUX_RGBImageRec* g, AUX_RGBImageRec* b)
{
	ReadEags = r;
	BlueEags = b;
	GrenEags = g;

	BackReck.SetObgect(Point(center.x - ReadEags->sizeX * 0.15, center.y - ReadEags->sizeY * 0.15), Point(center.x + ReadEags->sizeX * 0.15, center.y + ReadEags->sizeY * 0.15));

	if (prise < 30)
		Prise = -2;
	else if (prise > 80)
		Prise = 2;
	else Prise = 1;
}

void EagsObject::SetImage(AUX_RGBImageRec* r, AUX_RGBImageRec* g, AUX_RGBImageRec* b)
{
	ReadEags = r;
	BlueEags = b;
	GrenEags = g;
}

void EagsObject::MoveCircl(int delta)
{
	BackReck.LeftPoint.y += delta;
	BackReck.RightPoint.y += delta;
}

void EagsObject::Draw(bool isDebage)
{
	if (ReadEags != nullptr && BlueEags != nullptr && GrenEags != nullptr)
	{
		glRasterPos3d(BackReck.LeftPoint.x, BackReck.LeftPoint.y, 1); // ������ ����� ���� ����������� ??????????????????????
		glPixelZoom(0.3, 0.3); // ������������ ��������������� �� ������ � ������
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // ������ �������� ����������� � ������

		if (Prise == -2)
		{
			glDrawPixels(ReadEags->sizeX, ReadEags->sizeY, // ������ � ������ � ��������
				GL_RGB, // ������ ����� ��������
				GL_UNSIGNED_BYTE, // ������ �������� ���������
				ReadEags->data); // ������ �����������
		}
		else if (Prise == 2)
		{
			glDrawPixels(BlueEags->sizeX, BlueEags->sizeY, // ������ � ������ � ��������
				GL_RGB, // ������ ����� ��������
				GL_UNSIGNED_BYTE, // ������ �������� ���������
				BlueEags->data); // ������ �����������
		}
		else
		{
			glDrawPixels(GrenEags->sizeX, GrenEags->sizeY, // ������ � ������ � ��������
				GL_RGB, // ������ ����� ��������
				GL_UNSIGNED_BYTE, // ������ �������� ���������
				GrenEags->data); // ������ �����������
		}
	}
	else throw std::exception("�� ����������������� ���� �� �����������");

	if(isDebage)
		BackReck.Draw();
}

Point EagsObject::GetLeftPoint()
{
	return BackReck.LeftPoint;
}

Point EagsObject::GetRightPoint()
{
	return BackReck.RightPoint;
}



EagsObject::~EagsObject()
{
}

#pragma warning( disable : 26451)
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include "WolfObject.h"
#include "Menu.h"
#include "Rectangl.h"
#include "Circl.h"
#include "Button.h"
#include "glaux.h"
#include "glut.h"

using namespace std;

enum Status
{
	StartMenu, 
	Game, 
	Pause,
	GameMode,
	EndGame
} GameStatus;

enum GameMode
{
	Simpl,
	Hard
} SelectGameMode;

//разммеры окна и матрицы
GLfloat windowWidth = 600;
GLfloat windowHeight = 600;
GLfloat MatrixWidth = 600;
GLfloat MatrixHeght = 600;

//элементы игры
string Account = "Account: ";
string Timer = "Time: ";
int CountCircls = 10;
int Counts = 0;
int Radius = 80;//60
int Time = 0;
int MaxTime = 60; // минута
Rectangl Basket;
vector<Circl> Circls;
Circl Red(Point(0, 0), 0, 0), Gren(Point(0, 0), 0, 0), Blue(Point(0, 0), 0, 0);

//Menu
Menu MainMenu, PauseMenu, MenuGameMode, MenuEndGame;

bool isDebuge = false;

//Mouse
Point SaveMousePosition;

//Wolf
WolfObject Wolf;

//Image
AUX_RGBImageRec *pImage = nullptr;

//
void RenderScene(void);
void ChangeSize(int, int);
void SkeyboardFunc(int, int, int);
void MouseMove(int, int);
void PosiveMotionMauseMove(int, int);
void MousePress(int, int, int, int);
void KeyBoardFunc(unsigned char, int, int);

//таймеры
void TimerFunction(int);
void TimerMoveCircl(int);
void TimerCreateCircls(int);
void TimerEnd(int);

//button func
void Button9StartMenu();

//начальные установки меню 
void InichialParams();

void image_load()
{
	pImage = auxDIBImageLoad("wolv2.bmp");
}

void DrawFigures()
{
	glRasterPos3d(400, 0, 1); // Нижний левый угол изображения ??????????????????????
	glPixelZoom(1, 1); // Коэффициенты масштабирования по ширине и высоте
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Способ хранения изображения в памяти
	glDrawPixels(pImage->sizeX, pImage->sizeY, // Ширина и высота в пикселах
		GL_RGB, // Формат цвета пикселов
		GL_UNSIGNED_BYTE, // Формат цветовых компонент
		pImage->data); // Данные изображения
}

int main(int argc, char* argv[])
{
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Lab22_b");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SkeyboardFunc);
	glutKeyboardFunc(KeyBoardFunc);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(PosiveMotionMauseMove);
	glutMouseFunc(MousePress);

	glutTimerFunc(33, TimerFunction, 10);
	glutTimerFunc(33, TimerMoveCircl, 1);
	glutTimerFunc(33, TimerCreateCircls, 600);
	glutTimerFunc(33, TimerEnd, 1000);

	MatrixWidth = windowWidth = glutGet(GLUT_SCREEN_WIDTH);
	MatrixHeght = windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

	image_load();
	InichialParams();

	glutFullScreen();
	glutMainLoop();
	return 0;
}

void InichialParams()
{
	Circl red(Point(20, MatrixHeght / 2 + 50), 20, 10), gren(Point(20, MatrixHeght / 2), 20, 50), blue(Point(20, MatrixHeght /2 - 50), 20, 90);
	Red = red;
	Gren = gren;
	Blue = blue;

	GameStatus = StartMenu;
	Basket.SetObgect(Point(MatrixWidth / 2 - Radius, 20), Point(MatrixWidth / 2 + Radius, 20 + 30));
	Wolf.SetObject(Rectangl(Point(MatrixWidth / 2 - Radius, 20 + 60), Point(MatrixWidth / 2 + Radius, 20 + 30 + 60)));
	Wolf.SetImage(pImage);

	MainMenu.SetFon(Point(MatrixWidth / 2, MatrixHeght / 2), 80, 150, 2);
	MainMenu.SetColorCircuit(0.0f, 1.0f, 0.0f);
	MainMenu.SetColorFon(1.0f, 1.0f, 1.0f);
	MainMenu.SetText("Menu", MatrixWidth / 2, MatrixHeght / 2 + 140);

	PauseMenu.SetFon(Point(MatrixWidth / 2, MatrixHeght / 2), 80, 150, 2);
	PauseMenu.SetColorCircuit(0.0f, 1.0f, 0.0f);
	PauseMenu.SetColorFon(1.0f, 1.0f, 1.0f);
	PauseMenu.SetText("Pause", MatrixWidth / 2, MatrixHeght / 2 + 140);

	MenuGameMode.SetFon(Point(MatrixWidth / 2, MatrixHeght / 2), 80, 150, 2);
	MenuGameMode.SetColorCircuit(0.0f, 1.0f, 0.0f);
	MenuGameMode.SetColorFon(1.0f, 1.0f, 1.0f);
	MenuGameMode.SetText("Select game mode", MatrixWidth / 2, MatrixHeght / 2 + 140);

	MenuEndGame.SetFon(Point(MatrixWidth / 2, MatrixHeght / 2), 80, 150, 2);
	MenuEndGame.SetColorCircuit(0.0f, 1.0f, 0.0f);
	MenuEndGame.SetColorFon(1.0f, 1.0f, 1.0f);
	MenuEndGame.SetText("End Game", MatrixWidth / 2, MatrixHeght / 2 + 140);

	Button But1, But2, But3, But4, But5, But6, But7, But8, But9, But10;
	//main
	But1.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 110), 60, 20, 2, []() { GameStatus = Game; }, "Start a game!");
	But1.SetBack(0, 1, 0);
	But1.SetFront(1, 1, 1);

	But8.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 60), 60, 20, 2, []() { GameStatus = GameMode; }, "Game Mode");
	But8.SetBack(0, 1, 0);
	But8.SetFront(1, 1, 1);

	But4.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 10), 60, 20, 2, []() { isDebuge = !isDebuge; }, "Debage!!");
	But4.SetBack(1, 0, 0);
	But4.SetFront(1, 1, 1);

	But3.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 - 110), 60, 20, 2, []() { exit(0); }, "Exit");
	But3.SetBack(0, 1, 0);
	But3.SetFront(1, 1, 1);
	//pause
	But9.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 110), 60, 20, 2, Button9StartMenu, "Start menu");
	But9.SetBack(0, 1, 0);
	But9.SetFront(1, 1, 1);

	But2.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 60), 60, 20, 2, []() { GameStatus = Game; }, "Continue");
	But2.SetBack(0, 1, 0);
	But2.SetFront(1, 1, 1);

	But10.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 10), 60, 20, 2, []() { isDebuge = !isDebuge; }, "Debage!!");
	But10.SetBack(1, 0, 0);
	But10.SetFront(1, 1, 1);
	//game mode
	But5.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 110), 60, 20, 2, []() { SelectGameMode = Simpl; }, "Simple");
	But5.SetBack(0, 1, 0);
	But5.SetFront(1, 1, 1);

	But6.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 + 60), 60, 20, 2, []() { SelectGameMode = Hard; }, "Hard");
	But6.SetBack(0, 1, 0);
	But6.SetFront(1, 1, 1);

	But7.SetObject(Point(MatrixWidth / 2, MatrixHeght / 2 - 110), 60, 20, 2, []() { GameStatus = StartMenu; }, "Backward");
	But7.SetBack(0, 1, 0);
	But7.SetFront(1, 1, 1);

	MainMenu.AddButton(But1);
	MainMenu.AddButton(But8);
	MainMenu.AddButton(But4);
	MainMenu.AddButton(But3);

	PauseMenu.AddButton(But9);
	PauseMenu.AddButton(But2);
	PauseMenu.AddButton(But10);
	PauseMenu.AddButton(But3);

	MenuGameMode.AddButton(But5);
	MenuGameMode.AddButton(But6);
	MenuGameMode.AddButton(But7);

	MenuEndGame.AddButton(But9);
	MenuEndGame.AddButton(But3);

}

void Button9StartMenu()
{
	GameStatus = StartMenu; 
	Counts = 0;
	Time = 0;
	Basket.SetObgect(Point(MatrixWidth / 2 - Radius, 20), Point(MatrixWidth / 2 + Radius, 20 + 30));
	Circls.erase(Circls.begin(), Circls.end());
}

void TextXY(const char* text, int x, int y)
{
	glRasterPos2i(x, y); //позиция текста
	for (int i = 0; i < strlen(text); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void MousePress(int button, int state, int x, int y)
{
	y = MatrixHeght - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (GameStatus == StartMenu)
		{
			MainMenu.MousePressButtons(x, y);
		}
		else if (GameStatus == Pause)
		{
			PauseMenu.MousePressButtons(x, y);
		}
		else if (GameStatus == GameMode)
		{
			MenuGameMode.MousePressButtons(x, y);
		}
		else if (GameStatus == EndGame)
		{
			MenuEndGame.MousePressButtons(x, y);
		}
	}
}

void PosiveMotionMauseMove(int x, int y)
{
	y = MatrixHeght - y;
	if (GameStatus == StartMenu)
	{
		MainMenu.MouseInButtins(x, y);
	}
	else if (GameStatus == Pause)
	{
		PauseMenu.MouseInButtins(x, y);
	}
	else if (GameStatus == GameMode)
	{
		MenuGameMode.MouseInButtins(x, y);
	}
	else if (GameStatus == EndGame)
	{
		MenuEndGame.MouseInButtins(x, y);
	}
}

void MouseMove(int x, int y)
{
	if (GameStatus == Game)
	{
		if (x < 3 * MatrixWidth / 4 - Radius - 5 && x > MatrixWidth / 4 + Radius + 5)
		{
			Basket.LeftPoint.x = x - Radius;
			Basket.RightPoint.x = x + Radius;
			Wolf.SetNewCoord(x, 0);
		}
		else if (x == 3 * MatrixWidth / 4 - Radius - 5)
		{
			Basket.LeftPoint.x = x - Radius - 5;
			Basket.RightPoint.x = x + Radius - 5;
			Wolf.SetNewCoord(x - 5, 0);
		}
		else if (x == MatrixWidth / 4 + Radius + 5)
		{
			Basket.LeftPoint.x = x - Radius + 5;
			Basket.RightPoint.x = x + Radius + 5;
			Wolf.SetNewCoord(x + 5, 0);
		}
	}
}

void RenderGame()
{
	glColor3f(0.0f, 0.0f, 0.0f);

	//Basket.Draw(true);
	Wolf.Darw();

	for (int i = 0; i < Circls.size(); i++)
		Circls[i].Draw(isDebuge, SelectGameMode == Hard);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(MatrixWidth / 4, 0);
	glVertex2d(MatrixWidth / 4, MatrixHeght);
	glVertex2d(MatrixWidth / 4 * 3, 0);
	glVertex2d(MatrixWidth / 4 * 3, MatrixHeght);
	glVertex2d(0, MatrixHeght - 13);
	glVertex2d(MatrixWidth, MatrixHeght - 13);
	glEnd();

	string rez = Account + to_string(Counts);
	TextXY(rez.c_str(), 2, MatrixHeght - 11);

	string time = Timer + to_string(Time);
	TextXY(time.c_str(), rez.size() * 9 + 9, MatrixHeght - 11);

	if(isDebuge)
		TextXY("Debage!!", rez.size() * 9 + 9 + time.size() * 9 + 9, MatrixHeght - 11);

	switch (SelectGameMode)
	{
		case Simpl:
		{
			TextXY("Game mode: Simpl", 2, MatrixHeght / 2 + 65 + 10);
			Red.Draw(); TextXY(" = -2", 60, MatrixHeght / 2 + 45);
			Gren.Draw(); TextXY(" = 1", 60, MatrixHeght / 2 - 5);
			Blue.Draw(); TextXY(" = 2", 60, MatrixHeght / 2 - 55);
			break;
		}
		case Hard:
		{
			TextXY("Game mode: Hard(!!!)", 2, MatrixHeght / 2 + 20 + 10);
			Gren.Draw(); TextXY(" = ?", 60, MatrixHeght / 2 - 5);
			break;
		}
		default:
			break;
	}

	switch (GameStatus)
	{
		case StartMenu:
		{
			MainMenu.Draw();
			break;
		}
		case Game:
		{
			RenderGame();
			break;
		}
		case Pause:
		{
			RenderGame();
			PauseMenu.Draw();
			break;
		}
		case GameMode:
		{
			MenuGameMode.Draw();
			break;
		}
		case EndGame:
		{
			RenderGame();
			MenuEndGame.Draw();
			TextXY(rez.c_str(), MatrixWidth / 2 - rez.size() * 4.5, MatrixHeght / 2);
		}
		default:
			break;
	}

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(value, TimerFunction, value);
}

void TimerEnd(int value)
{
	if (GameStatus == Game)
	{
		if (Time < MaxTime)
			Time++;
		else if (Time == MaxTime)
			GameStatus = EndGame;
	}

	glutTimerFunc(value, TimerEnd, value);
}

void TimerMoveCircl(int value)
{
	if (GameStatus == Game)
	{
		for (int i = 0; i < Circls.size();)
		{
			Circls[i].Centr.y -= 1;

			if (Circls[i].Centr.y - Circls[i].radius <= Wolf.GetRightPoint().y && Circls[i].Centr.x + Circls[i].radius >= Wolf.GetLeftPoint().x && Circls[i].Centr.x - Circls[i].radius <= Wolf.GetRightPoint().x && Circls[i].Centr.y + Circls[i].radius >= Wolf.GetLeftPoint().y)
			{
				Counts += Circls[i].Prise;
				Circls.erase(Circls.begin() + i, Circls.begin() + i + 1);
				continue;
			}

			if (Circls[i].Centr.y - Circls[i].radius <= 10)
			{
				Circls.erase(Circls.begin() + i, Circls.begin() + i + 1);
				continue;
			}

			i++;
		}
	}

	glutTimerFunc(value, TimerMoveCircl, value);
}

void TimerCreateCircls(int value)
{
	if (GameStatus == Game)
	{
		int count = rand() % 3 + 1;
		int radius = 20;

		for (int i = 0; i < count; i++)
		{
			int x = rand() % (int)(MatrixWidth / 2 - 2 * radius) + MatrixWidth / 4 + radius,
				y = MatrixHeght - 13 - radius;
			Circls.push_back(Circl(Point(x , y), radius, rand() % 100));
		}

		if (count != 1)
		{
			for (int i = Circls.size() - count; i < Circls.size() - 1; i++)
			{
				for (int j = i + 1; j < Circls.size(); j++)
				{
					double L = abs(Circls[j].Centr.x - Circls[i].Centr.x);
					double R = Circls[j].radius + Circls[i].radius;

					if (L >= R)
						continue;

					Circls[j].isIntr = true;
					Circls[i].isIntr = true;

					double move1 = (R - L) / 2 + 1, move2 = (R - L) / 2 + 1;

					if (Circls[i].Centr.x < Circls[j].Centr.x)
					{
						int razn1 = Circls[i].Centr.x - Circls[i].radius - MatrixWidth / 4;
						int razn2 = 3 * MatrixWidth / 4 - Circls[j].Centr.x - Circls[j].radius;

						if (razn1 < move1)
						{
							move2 += move1 - razn1;
							move1 = razn1;
						}
						else if (razn2 < move2)
						{
							move1 += move2 - razn2;
							move2 = razn2;
						}

						Circls[i].Centr.x -= move1;
						Circls[j].Centr.x += move2;
					}
					else
					{
						int razn1 = Circls[j].Centr.x - Circls[j].radius - MatrixWidth / 4;
						int razn2 = 3 * MatrixWidth / 4 - Circls[i].Centr.x - Circls[i].radius;

						if (razn1 < move1)
						{
							move2 += move1 - razn1;
							move1 = razn1;
						}
						else if (razn2 < move2)
						{
							move1 += move2 - razn2;
							move2 = razn2;
						}

						Circls[i].Centr.x += move1;
						Circls[j].Centr.x -= move2;
					}
				}
			}
		}
	}

	glutTimerFunc(value, TimerCreateCircls, value);
}

void ChangeSize(int width, int height)
{
	//glutReshapeWindow(windowWidth, windowHeight);
	MatrixWidth = windowWidth = width;
	MatrixHeght = windowHeight = height;
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, MatrixWidth, 0, MatrixHeght, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SkeyboardFunc(int key, int x, int y)
{
	int move = 60;
	switch (key)
	{
		case GLUT_KEY_END: exit(0);
		default:
			break;
	}

}

void KeyBoardFunc(unsigned char key, int x, int y)
{
	if (key == 27 && (GameStatus == Game || GameStatus == Pause))
		GameStatus = GameStatus != Pause ? Pause : Game;
}
#include "view.h"
#include "easyx.h"
#include "Enemy.h"
#include "SmallEnemy.h"

IMAGE boom1, boom2, boom3, boom4;
IMAGE smallboom1, smallboom2, smallboom3, smallboom4;
IMAGE addBlood,addBlood1;

void LoadBoom()
{
	loadimage(&boom1, _T("res\\boom\\boom1.png"));
	loadimage(&boom2, _T("res\\boom\\boom2.png"));
	loadimage(&boom3, _T("res\\boom\\boom3.png"));
	loadimage(&boom4, _T("res\\boom\\boom4.png"));

	loadimage(&smallboom1, _T("res\\boom\\smallboom1.png"));
	loadimage(&smallboom2, _T("res\\boom\\smallboom2.png"));
	loadimage(&smallboom3, _T("res\\boom\\smallboom3.png"));
	loadimage(&smallboom4, _T("res\\boom\\smallboom4.png"));
}

void InitGame()
{
	LoadBoom();
	PlaySound(TEXT("res\\music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// 初始化开始界面窗口
	loadimage(&background, _T("res\\sky2.png"), GAMEWIDTH, GAMEHIGHT, true);
	putimage(0, 0, &background);		// 开始界面



	system("pause");
	cleardevice();
	// 加载飞机
	loadimage(&ship, _T("res\\redship.png"));
	loadimage(&ship1, _T("res\\redship1.png"));

	// 加载敌机
	loadimage(&enemy, _T("res\\enemyxx.png"));
	loadimage(&enemy1, _T("res\\enemyxx1.png"));

	// 加载小敌机
	loadimage(&smallenemy, _T("res\\smallenemy.png"));
	loadimage(&smallenemy1, _T("res\\smallenemy1.png"));

	//加载加血包图片
	loadimage(&addBlood, _T("res\\addBlood.jpg"));
	loadimage(&addBlood1, _T("res\\addBlood1.jpg"));


	for (int i = 0; i < 5; i++) {
		myenemy[i].direction = DOWN;
		myenemy[i].m_nStartHight = 0;
		myenemy[i].m_Move = 0;
		myenemy[i].m_Fire = 0;
		myenemy[i].m_Boom = 0;
	}
}

void ShowBullet()
{
	// 显示飞船子弹
	for (Iter = VectorBullets0.begin(); Iter != VectorBullets0.end(); Iter++)
	{
		if (VectorBullets0.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveUp();
		(*Iter)->ShowYellow();
	}

	for (Iter1 = VectorBullets1.begin(); Iter1 != VectorBullets1.end(); Iter1++)
	{
		if (VectorBullets1.size() == 0)
		{
			break;
		}
		if (*Iter1 == nullptr)
		{
			break;
		}
		(*Iter1)->ShowClear1();
		(*Iter1)->MoveUp1();
		(*Iter1)->ShowRed1();
	}

	for (Iter2 = VectorBullets2.begin(); Iter2 != VectorBullets2.end(); Iter2++)
	{
		if (VectorBullets2.size() == 0)
		{
			break;
		}
		if (*Iter2 == nullptr)
		{
			break;
		}
		(*Iter2)->ShowClear2();
		(*Iter2)->MoveUp2();
		(*Iter2)->ShowRed2();
	}

	for (Iter3 = VectorBullets3.begin(); Iter3 != VectorBullets3.end(); Iter3++)
	{
		if (VectorBullets3.size() == 0)
		{
			break;
		}
		if (*Iter3 == nullptr)
		{
			break;
		}
		(*Iter3)->ShowClear3();
		(*Iter3)->MoveUp3();
		(*Iter3)->ShowRed3();
	}

	for (Iter4 = VectorBullets4.begin(); Iter4 != VectorBullets4.end(); Iter4++)
	{
		if (VectorBullets4.size() == 0)
		{
			break;
		}
		if (*Iter4 == nullptr)
		{
			break;
		}
		(*Iter4)->ShowClear4();
		(*Iter4)->MoveUp4();
		(*Iter4)->ShowRed4();
	}

	// 显示敌机子弹
	for (Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveDown();
		(*Iter)->ShowRed();
	}
}

void ShowInPut()
{
	if (myinput & UPINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & DOWNINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & LEFTINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & RIGHTINPUT)
	{
		myship.ShowClear();
	}
}
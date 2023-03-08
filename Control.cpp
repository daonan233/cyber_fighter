#include <conio.h>
#include <easyx.h>
#include <iostream>
#include <array>
#include "control.h"
#include "Enemy.h"
#include "view.h"
#include "SmallEnemy.h"
#include "GameControl.h"
#include "Bullet.h"
#include "BloodBuff.h"
#include "Trajectory.h"

IMAGE endImage;

CShip myship(GAMEWIDTH / 2 - 20, GAMEHIGHT - 60, 100);		// 飞船位置，血量
std::array<CEnemy, 5> myenemy{ CEnemy{GAMEWIDTH / 2 - 50, 20, 100}, CEnemy{GAMEWIDTH / 2 - 100, 20, 100},
CEnemy{GAMEWIDTH / 3 - 50, 20, 200} , CEnemy{GAMEWIDTH / 4 + 50, 20, 10} , CEnemy{GAMEWIDTH / 5 + 40, 20, 20} };	// 敌机位置，血量
CSmallEnemy mysmallenemy(0, 0);							// 小敌机
CGameControl mygamecontrol;									// 游戏控制

IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;
vector<CBullet*> VectorBullets0;
vector<RBullet1*> VectorBullets1;
vector<RBullet2*> VectorBullets2;
vector<RBullet3*> VectorBullets3;
vector<RBullet4*> VectorBullets4;

vector<CBullet*> VectorEnenyBullets;
vector<CBullet*>::iterator Iter;
vector<RBullet1*>::iterator Iter1;
vector<RBullet2*>::iterator Iter2;
vector<RBullet3*>::iterator Iter3;
vector<RBullet4*>::iterator Iter4;
vector<CGameRole*> RoleVector;
BloodBuff bloodbuff;
std::array<int, 2> velocity{ 2, 2 };


clock_t ClkMakeBulletStart = clock();
clock_t ClkMakeBulletFinish = clock();						// 飞船产生子弹

bool GameOver()
{
	for (int i = 0; i < 5; i++) {
		// 飞机和敌人碰撞
		if (((myship.m_nRow >= myenemy[i].m_nRow) && (myship.m_nRow <= myenemy[i].m_nRow + enemy.getwidth()))
			&& ((myship.m_nCol <= myenemy[i].m_nCol + enemy.getheight()) && ((myship.m_nCol >= myenemy[i].m_nCol))))
		{
			return true;
		}

		// 敌机碰到下边缘
		if (myenemy[i].m_nCol + enemy.getheight() > GAMEHIGHT)
		{
			return true;
		}

		// 飞船血量为0
		if (myship.m_nLife <= 0)
		{
			if (myship.m_Boom == 15)
			{
				return true;
			}
			if (myship.m_Boom == 0)
			{
				myship.m_Boom = 1;
			}
		}
	}
	return false;
}

int HandleGameOver()
{
	if (GameOver())
	{
		mciSendString(_T("close MySong"), NULL, 0, NULL);

		// 清空数组
		for (size_t i = 0; i < VectorBullets0.size(); i++)
		{
			VectorBullets0.pop_back();
		}
		for (size_t i = 0; i < VectorBullets1.size(); i++)
		{
			VectorBullets1.pop_back();
		}
		for (size_t i = 0; i < VectorBullets2.size(); i++)
		{
			VectorBullets2.pop_back();
		}

		for (size_t i = 0; i < VectorEnenyBullets.size(); i++)
		{
			VectorEnenyBullets.pop_back();
		}

		cleardevice();

		// 游戏结束提示
		mygamecontrol.ShowScore();

		loadimage(&endImage, _T("res\\end.png"));
		putimage(0, 0, &endImage);
		while (_kbhit())
		{
			_getch();
		}

		char chInPut = '\0';
		chInPut = _getch();

		if (chInPut == 'R' || chInPut == 'r')
		{
			return -2;
		}
		if (chInPut == 27)
		{
			return -1;
		}
	}
	return 1;
}

int myinput = NOINPUT;

void GetOrder()
{
	ClkMakeBulletFinish = clock();		// 飞船子弹产生时间差

	if (GetAsyncKeyState('W') & 0x8000)
	{
		myinput |= UPINPUT;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		myinput |= DOWNINPUT;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		myinput |= LEFTINPUT;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		myinput |= RIGHTINPUT;
	}

	if (GetAsyncKeyState('K')&&ClkMakeBulletFinish - ClkMakeBulletStart > 50)
	{
		// 飞船子弹
		myinput |= FIREINPUT;
		ClkMakeBulletStart = ClkMakeBulletFinish;
	}

	if (GetAsyncKeyState(' ') & 0x8000)
	{
		myinput |= SPACEINPUT;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		myinput |= ESCINPUT;
	}
}

void DealInPut()
{
	if ((myinput & UPINPUT) && (myship.m_nCol >= 10))
	{
		myship.m_nCol -= 3;
	}

	if ((myinput & DOWNINPUT) && (myship.m_nCol <= GAMEHIGHT - ship.getheight() - 10))
	{
		myship.m_nCol += 3;
	}

	if ((myinput & LEFTINPUT) && (myship.m_nRow >= 10))
	{
		myship.m_nRow -= 3;
	}

	if ((myinput & RIGHTINPUT) && (myship.m_nRow <= GAMEWIDTH - ship.getwidth() - 10))
	{
		myship.m_nRow += 3;
	}

	if (myinput & FIREINPUT)
	{
		CBullet* pNewBullet0 = new CBullet(myship.m_nRow + ((ship.getwidth() / 2)), myship.m_nCol - 5);
		RBullet1* pNewBullet1 = new RBullet1(myship.m_nRow + ((ship.getwidth() / 2 + 10)), myship.m_nCol - 5);
		RBullet2* pNewBullet2 = new RBullet2(myship.m_nRow + ((ship.getwidth() / 2 - 10)), myship.m_nCol - 5);
		RBullet3* pNewBullet3 = new RBullet3(myship.m_nRow + ((ship.getwidth() / 2 + 10)), myship.m_nCol - 5);
		RBullet4* pNewBullet4 = new RBullet4(myship.m_nRow + ((ship.getwidth() / 2 - 10)), myship.m_nCol - 5);
		VectorBullets0.push_back(pNewBullet0);
		VectorBullets1.push_back(pNewBullet1);
		VectorBullets2.push_back(pNewBullet2);
		VectorBullets3.push_back(pNewBullet3);
		VectorBullets4.push_back(pNewBullet4);
	}

	if (myinput & SPACEINPUT)
	{

		_getch();
	}

	if (myinput & ESCINPUT)
	{
		exit(0);
	}

	myinput = NOINPUT;
}

void EnemyMove() {
	for (int i = 0; i < 5; i++) {
		// 掩盖敌机
		myenemy[i].ShowClear();

		// 掩盖敌机的血量
		myenemy[i].ShowClearLife();

		if (myenemy[i].m_Move % 10 == 0)
		{
			cleardevice();
			if (myenemy[i].m_nCol < 0)
			{
				myenemy[i].MoveDown();
			}

			if (myenemy[i].direction == DOWN)
			{
				myenemy[i].MoveDown();

				if (myenemy[i].m_nCol >= myenemy[i].m_nStartHight + 20)
				{
					myenemy[i].direction = Right;
				}
			}

			if (myenemy[i].direction == Right)
			{
				myenemy[i].MoveRight();

				if (myenemy[i].m_nRow >= GAMEWIDTH - enemy.getwidth())
				{
					myenemy[i].direction = Left;
				}
			}

			if (myenemy[i].direction == Left)
			{
				myenemy[i].MoveLeft();

				if (myenemy[i].m_nRow <= 0)
				{
					myenemy[i].direction = DOWN;
					myenemy[i].m_nStartHight = myenemy[i].m_nCol;
				}
			}
			// 掩盖小敌机
			mysmallenemy.ShowClear();

			// 随机小敌机的自动下移
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.MoveDown();
			}

			bloodbuff.showBuffImage();

			if (!bloodbuff.hasReceived)
				bloodbuff.ImageMov(visit1, velocity);
		}
	}
}

void isHasBeenEated() {
	bloodbuff.isReceived(myship);
	if (bloodbuff.hasReceived) {
		bloodbuff.exeBuff(0, 0, myship);
		GetNewBuff();
	}
}

void MakeEnemyBullet()
{
	for (int i = 0; i < 5; i++) {
		if (myenemy[i].m_Fire % (70) == 0)
		{
			// 创造敌机子弹
			CBullet* pNewEnemyBullet = new CBullet(myenemy[i].m_nRow + enemy.getwidth() / 2, myenemy[i].m_nCol + enemy.getheight());
			VectorEnenyBullets.push_back(pNewEnemyBullet);
		}
	}
}

void DeleteMemory()
{
	// 飞船子弹到上边界释放
	for (vector<CBullet*>::iterator Iter = VectorBullets0.begin(); Iter != VectorBullets0.end();)
	{
		if (VectorBullets0.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if ((*Iter)->m_nCol < 0)
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorBullets0.erase(Iter);
			Iter = VectorBullets0.begin();
		}

		if (VectorBullets0.size() != 0)

		{
			Iter++;
		}
	}


	for (vector<RBullet1*>::iterator Iter1 = VectorBullets1.begin(); Iter1 != VectorBullets1.end();)
	{
		if (VectorBullets1.size() == 0)
		{
			break;
		}
		if (*Iter1 == nullptr)
		{
			break;
		}
		if ((*Iter1)->m_nCol1 < 0)
		{
			(*Iter1)->ShowClear1();
			delete* Iter1;
			*Iter1 = nullptr;
			VectorBullets1.erase(Iter1);
			Iter1 = VectorBullets1.begin();
		}

		if (VectorBullets1.size() != 0)
		{
			Iter1++;
		}
	}



	for (vector<RBullet2*>::iterator Iter2 = VectorBullets2.begin(); Iter2 != VectorBullets2.end();)
	{
		if (VectorBullets2.size() == 0)
		{
			break;
		}
		if (*Iter2 == nullptr)
		{
			break;
		}
		if ((*Iter2)->m_nCol2 < 0)
		{
			(*Iter2)->ShowClear2();
			delete* Iter2;
			*Iter2 = nullptr;
			VectorBullets2.erase(Iter2);
			Iter2 = VectorBullets2.begin();
		}

		if (VectorBullets2.size() != 0)
		{
			Iter2++;
		}
	}

	for (vector<RBullet3*>::iterator Iter3 = VectorBullets3.begin(); Iter3 != VectorBullets3.end();)
	{
		if (VectorBullets3.size() == 0)
		{
			break;
		}
		if (*Iter3 == nullptr)
		{
			break;
		}
		if ((*Iter3)->m_nCol3 < 0)
		{
			(*Iter3)->ShowClear3();
			delete* Iter3;
			*Iter3 = nullptr;
			VectorBullets3.erase(Iter3);
			Iter3 = VectorBullets3.begin();
		}

		if (VectorBullets3.size() != 0)
		{
			Iter3++;
		}
	}


	for (vector<RBullet4*>::iterator Iter4 = VectorBullets4.begin(); Iter4 != VectorBullets4.end();)
	{
		if (VectorBullets4.size() == 0)
		{
			break;
		}
		if (*Iter4 == nullptr)
		{
			break;
		}
		if ((*Iter4)->m_nCol4 < 0)
		{
			(*Iter4)->ShowClear4();
			delete* Iter4;
			*Iter4 = nullptr;
			VectorBullets4.erase(Iter4);
			Iter4 = VectorBullets4.begin();
		}

		if (VectorBullets4.size() != 0)
		{
			Iter4++;
		}
	}

}

void IsEnenmyHurt()
{
	// 判断敌机是否中弹
	for (vector<CBullet*>::iterator Iter = VectorBullets0.begin(); Iter != VectorBullets0.end(); Iter++)
	{
		if (VectorBullets0.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		for (int i = 0; i < 5; i++) {
			if (((*Iter)->m_nRow >= myenemy[i].m_nRow && (*Iter)->m_nRow <= myenemy[i].m_nRow + enemy.getwidth())
				&& ((*Iter)->m_nCol <= myenemy[i].m_nCol + enemy.getheight() && (*Iter)->m_nCol >= myenemy[i].m_nCol))
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
				delete* Iter;
				*Iter = nullptr;
				VectorBullets0.erase(Iter);
				Iter = VectorBullets0.begin();
				// 掩盖敌机血量
				myenemy[i].ShowClearLife();
				// 敌机受伤血量减5
				myenemy[i].GetHit();
				break;
			}
		}
	}

	for (vector<RBullet1*>::iterator Iter1 = VectorBullets1.begin(); Iter1 != VectorBullets1.end(); Iter1++)
	{
		if (VectorBullets1.size() == 0)
		{
			break;
		}
		if (*Iter1 == nullptr)
		{
			break;
		}
		for (int i = 0; i < 5; i++) {
			if (((*Iter1)->m_nRow1 >= myenemy[i].m_nRow && (*Iter1)->m_nRow1 <= myenemy[i].m_nRow + enemy.getwidth())
				&& ((*Iter1)->m_nCol1 <= myenemy[i].m_nCol + enemy.getheight() && (*Iter1)->m_nCol1 >= myenemy[i].m_nCol))
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
				delete* Iter1;
				*Iter1 = nullptr;
				VectorBullets1.erase(Iter1);
				Iter1 = VectorBullets1.begin();
				// 掩盖敌机血量
				myenemy[i].ShowClearLife();
				// 敌机受伤血量减5
				myenemy[i].GetHit();
				break;
			}
		}
	}

	for (vector<RBullet2*>::iterator Iter2 = VectorBullets2.begin(); Iter2 != VectorBullets2.end(); Iter2++)
	{
		if (VectorBullets2.size() == 0)
		{
			break;
		}
		if (*Iter2 == nullptr)
		{
			break;
		}
		for (int i = 0; i < 5; i++) {
			if (((*Iter2)->m_nRow2 >= myenemy[i].m_nRow && (*Iter2)->m_nRow2 <= myenemy[i].m_nRow + enemy.getwidth())
				&& ((*Iter2)->m_nCol2 <= myenemy[i].m_nCol + enemy.getheight() && (*Iter2)->m_nCol2 >= myenemy[i].m_nCol))
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
				delete* Iter2;
				*Iter2 = nullptr;
				VectorBullets2.erase(Iter2);
				Iter2 = VectorBullets2.begin();
				// 掩盖敌机血量
				myenemy[i].ShowClearLife();
				// 敌机受伤血量减5
				myenemy[i].GetHit();
				break;
			}
		}
	}

	for (vector<RBullet3*>::iterator Iter3 = VectorBullets3.begin(); Iter3 != VectorBullets3.end(); Iter3++)
	{
		if (VectorBullets3.size() == 0)
		{
			break;
		}
		if (*Iter3 == nullptr)
		{
			break;
		}
		for (int i = 0; i < 5; i++) {
			if (((*Iter3)->m_nRow3 >= myenemy[i].m_nRow && (*Iter3)->m_nRow3 <= myenemy[i].m_nRow + enemy.getwidth())
				&& ((*Iter3)->m_nCol3 <= myenemy[i].m_nCol + enemy.getheight() && (*Iter3)->m_nCol3 >= myenemy[i].m_nCol))
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
				delete* Iter3;
				*Iter3 = nullptr;
				VectorBullets3.erase(Iter3);
				Iter3 = VectorBullets3.begin();
				// 掩盖敌机血量
				myenemy[i].ShowClearLife();
				// 敌机受伤血量减5
				myenemy[i].GetHit();
				break;
			}
		}
	}

	for (vector<RBullet4*>::iterator Iter4 = VectorBullets4.begin(); Iter4 != VectorBullets4.end(); Iter4++)
	{
		if (VectorBullets4.size() == 0)
		{
			break;
		}
		if (*Iter4 == nullptr)
		{
			break;
		}
		for (int i = 0; i < 5; i++) {
			if (((*Iter4)->m_nRow4 >= myenemy[i].m_nRow && (*Iter4)->m_nRow4 <= myenemy[i].m_nRow + enemy.getwidth())
				&& ((*Iter4)->m_nCol4 <= myenemy[i].m_nCol + enemy.getheight() && (*Iter4)->m_nCol4 >= myenemy[i].m_nCol))
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
				delete* Iter4;
				*Iter4 = nullptr;
				VectorBullets4.erase(Iter4);
				Iter4 = VectorBullets4.begin();
				// 掩盖敌机血量
				myenemy[i].ShowClearLife();
				// 敌机受伤血量减5
				myenemy[i].GetHit();
				break;
			}
		}
	}
}



void IsShipHurt()
{
	// 判断飞船是否中弹
	for (vector<CBullet*>::iterator Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= myship.m_nRow && (*Iter)->m_nRow <= myship.m_nRow + ship.getwidth())
			&& ((*Iter)->m_nCol <= myship.m_nCol + ship.getheight() && (*Iter)->m_nCol >= myship.m_nCol))
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorEnenyBullets.erase(Iter);
			Iter = VectorEnenyBullets.begin();

			// 掩盖飞船血量
			myship.ShowClearLife();
			myship.GetHit();
			cleardevice();
			if (VectorEnenyBullets.size() == 0)
			{
				break;
			}
		}
	}
}

void SmallHitShip()
{
	// 判断小敌机是否撞到飞船，撞到后飞船血量减少，小敌机消失重建
	if (((myship.m_nRow + (ship.getwidth() / 2) >= mysmallenemy.m_nRow) && (myship.m_nRow <= mysmallenemy.m_nRow + smallenemy.getwidth()))
		&& ((myship.m_nCol <= mysmallenemy.m_nCol + smallenemy.getheight()) && ((myship.m_nCol >= mysmallenemy.m_nCol))))
	{
		// 掩盖小敌机
		mysmallenemy.ShowClear();

		// 产生新小敌机
		mysmallenemy.m_nRow = rand() % (GAMEWIDTH - smallenemy.getwidth());
		mysmallenemy.m_nCol = 0;

		// 掩盖飞船血量
		myship.ShowClearLife();
		// 飞船血量减少
		myship.GetHit();
		cleardevice();
	}
}

bool IsBullertHitSmall()
{
	// 小敌机的再次产生，当中弹或者到达屏幕底部
	for (vector<CBullet*>::iterator Iter = VectorBullets0.begin(); Iter != VectorBullets0.end(); Iter++)
	{
		if (VectorBullets0.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		if (((*Iter)->m_nRow >= mysmallenemy.m_nRow && (*Iter)->m_nRow <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter)->m_nCol <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter)->m_nCol >= mysmallenemy.m_nCol))
		{
			(*Iter)->ShowClear();
			delete* Iter;
			*Iter = nullptr;
			VectorBullets0.erase(Iter);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			mygamecontrol.m_nScore += 10;
			return true;
		}
	}


	for (vector<RBullet1*>::iterator Iter1 = VectorBullets1.begin(); Iter1 != VectorBullets1.end(); Iter1++)
	{
		if (VectorBullets1.size() == 0)
		{
			break;
		}
		if (*Iter1 == nullptr)
		{
			break;
		}
		if (((*Iter1)->m_nRow1 >= mysmallenemy.m_nRow && (*Iter1)->m_nRow1 <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter1)->m_nCol1 <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter1)->m_nCol1 >= mysmallenemy.m_nCol))
		{
			(*Iter1)->ShowClear1();
			delete* Iter1;
			*Iter1 = nullptr;
			VectorBullets1.erase(Iter1);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			mygamecontrol.m_nScore += 10;
			return true;
		}
	}

	for (vector<RBullet2*>::iterator Iter2 = VectorBullets2.begin(); Iter2 != VectorBullets2.end(); Iter2++)
	{
		if (VectorBullets2.size() == 0)
		{
			break;
		}
		if (*Iter2 == nullptr)
		{
			break;
		}
		if (((*Iter2)->m_nRow2 >= mysmallenemy.m_nRow && (*Iter2)->m_nRow2 <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter2)->m_nCol2 <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter2)->m_nCol2 >= mysmallenemy.m_nCol))
		{
			(*Iter2)->ShowClear2();
			delete* Iter2;
			*Iter2 = nullptr;
			VectorBullets2.erase(Iter2);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			mygamecontrol.m_nScore += 10;
			return true;
		}
	}

	for (vector<RBullet3*>::iterator Iter3 = VectorBullets3.begin(); Iter3 != VectorBullets3.end(); Iter3++)
	{
		if (VectorBullets3.size() == 0)
		{
			break;
		}
		if (*Iter3 == nullptr)
		{
			break;
		}
		if (((*Iter3)->m_nRow3 >= mysmallenemy.m_nRow && (*Iter3)->m_nRow3 <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter3)->m_nCol3 <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter3)->m_nCol3 >= mysmallenemy.m_nCol))
		{
			(*Iter3)->ShowClear3();
			delete* Iter3;
			*Iter3 = nullptr;
			VectorBullets3.erase(Iter3);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			mygamecontrol.m_nScore += 10;
			return true;
		}
	}

	for (vector<RBullet4*>::iterator Iter4 = VectorBullets4.begin(); Iter4 != VectorBullets4.end(); Iter4++)
	{
		if (VectorBullets4.size() == 0)
		{
			break;
		}
		if (*Iter4 == nullptr)
		{
			break;
		}
		if (((*Iter4)->m_nRow4 >= mysmallenemy.m_nRow && (*Iter4)->m_nRow4 <= mysmallenemy.m_nRow + smallenemy.getwidth())
			&& ((*Iter4)->m_nCol4 <= mysmallenemy.m_nCol + smallenemy.getheight() && (*Iter4)->m_nCol4 >= mysmallenemy.m_nCol))
		{
			(*Iter4)->ShowClear4();
			delete* Iter4;
			*Iter4 = nullptr;
			VectorBullets4.erase(Iter4);
			if (mysmallenemy.m_Boom == 0)
			{
				mysmallenemy.m_Boom = 1;
			}
			mygamecontrol.m_nScore += 10;
			return true;
		}
	}
	return false;
}
bool SmallHitLow()
{
	if (mysmallenemy.m_nCol >= GAMEHIGHT)
	{
		return true;
	}
	return false;
}

void GetNewShip()
{
	// 产生新飞船
	myship.m_nRow = GAMEWIDTH / 2 - 20;
	myship.m_nCol = GAMEHIGHT - 60;
	myship.m_nLife = 1000;
	myship.m_Boom = 0;
}

void GetNewSmallEnemy()
{
	// 产生新小敌机
	mysmallenemy.m_nRow = rand() % (GAMEWIDTH - smallenemy.getwidth());
	mysmallenemy.m_nCol = 0;
	mysmallenemy.m_Boom = 0;
}

void GetNewBuff() {
	bloodbuff.buff_pos_x = rand() % (GAMEWIDTH - addBlood.getwidth());
	bloodbuff.buff_pos_y = 10;
	bloodbuff.hasReceived = false;
}

void GetNewEnemy(int i)
{
	// 敌机摧毁后新建一个敌机
	// 产生新敌机
	setfillcolor(BLACK);
	solidrectangle(myenemy[i].m_nRow, myenemy[i].m_nCol - 10, myenemy[i].m_nRow + myenemy[i].m_nLife, myenemy[i].m_nCol - 5);
	myenemy[i].m_nRow = rand() % (GAMEWIDTH - enemy.getwidth());
	myenemy[i].m_nCol = 20;

	myenemy[i].m_nLife = 200;
	myenemy[i].direction = DOWN;
	myenemy[i].m_nStartHight = myenemy[i].m_nCol;
	myenemy[i].m_Boom = 0;
	myenemy[i].m_Move = 0;
	myenemy[i].m_Fire = 0;
}

void HpSleep(int ms)
{
	static clock_t ClkGameFinish = clock();
	ClkGameFinish += ms * CLOCKS_PER_SEC / 1500;

	if (clock() > ClkGameFinish)
	{
		ClkGameFinish = clock();
	}
	else
	{
		while (clock() < ClkGameFinish)
		{
			Sleep(0.5);
		}
	}
}

void HandleBoom()
{
	for (int i = 0; i < 5; i++) {
		if (myenemy[i].m_Boom >= 1 && myenemy[i].m_Boom <= 14)
			myenemy[i].m_Boom++;

		if (mysmallenemy.m_Boom >= 1 && mysmallenemy.m_Boom <= 13)
			mysmallenemy.m_Boom++;

		for (int j = 0; j < 5; j++) {
			if (myenemy[j].m_nLife <= 0 && myenemy[j].m_Boom == 15) {
				cleardevice();
				GetNewEnemy(j);
			}
		}

		// 获得新敌机

		// 敌机爆炸开始条件
		if (myenemy[i].m_nLife <= 0 && myenemy[i].m_Boom == 0)
		{
			mygamecontrol.m_nScore += 100;
			myenemy[i].m_Boom = 1;
		}

		if (mysmallenemy.m_Boom == 0 && SmallHitLow() == true) //jile
		{
			GetNewSmallEnemy();
		}

		if (mysmallenemy.m_Boom == 14)
		{
			// 产生新小敌机
			GetNewSmallEnemy();
		}

		// 显示敌机和飞船
		if (myenemy[i].m_Boom == 0)
		{
			myenemy[i].Show();
		}

		// 显示随机小敌机
		if (mysmallenemy.m_Boom == 0)
		{
			mysmallenemy.Show();
		}

		if (myship.m_Boom >= 1 && myship.m_Boom <= 13)
		{
			myship.m_Boom++;
		}

		myenemy[i].m_Move++;
		myenemy[i].m_Fire++;
	}
}
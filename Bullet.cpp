#include <easyx.h>
#include "Enemy.h"
#include "Bullet.h"

/*CEnemy cem;
int acol = cem.m_nCol;
int arow = cem.m_nRow;*/

void CBullet::MoveUp()
{
	m_nCol -= 10;
}

void CBullet::ShowYellow()
{
	setfillcolor(YELLOW);
	solidcircle(m_nRow, m_nCol, 10);
}


void CBullet::ShowClear()				// ¸²¸Ç×Óµ¯
{
	setfillcolor(BLACK);
	solidcircle(m_nRow, m_nCol, 8);
}

void CBullet::MoveDown()
{
	m_nCol += 4;
}

CBullet::CBullet(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
}

void CBullet::ShowRed()
{
	setfillcolor(YELLOW);
	solidcircle(m_nRow, m_nCol, 6);
}



void RBullet1::MoveUp1()
{
	m_nCol1 -= 10;
	m_nRow1 += 1;
}

void RBullet1::ShowRed1()
{
	setfillcolor(RED);
	solidcircle(m_nRow1, m_nCol1, 5);
}


void RBullet1::ShowClear1()				// ¸²¸Ç×Óµ¯
{
	setfillcolor(WHITE);
	solidcircle(m_nRow1, m_nCol1, 2);
}

void RBullet1::MoveDown1()
{
	m_nCol1 += 6;
}

RBullet1::RBullet1(int nRow1, int nCol1)
{
	m_nRow1 = nRow1;
	m_nCol1 = nCol1;
}



void RBullet2::MoveUp2()
{
	m_nCol2 -= 10;
	m_nRow2 -= 1;
}

void RBullet2::ShowRed2()
{
	setfillcolor(RED);
	solidcircle(m_nRow2, m_nCol2, 5);
}


void RBullet2::ShowClear2()				// ¸²¸Ç×Óµ¯
{
	setfillcolor(WHITE);
	solidcircle(m_nRow2, m_nCol2, 2);
}

void RBullet2::MoveDown2()
{
	m_nCol2 += 10;
}

RBullet2::RBullet2(int nRow2, int nCol2)
{
	m_nRow2 = nRow2;
	m_nCol2 = nCol2;
}


void RBullet3::MoveUp3()
{

	m_nCol3 -= 10;
	m_nRow3 += 3;
	if (m_nCol3 == 5 || m_nCol3 == GAMEHIGHT - 5)
	{
		m_nCol3 = -m_nCol3;
	}
	if (m_nRow3 == 5 || m_nRow3 == GAMEWIDTH - 5)
	{
		m_nRow3 = -m_nRow3;
	}

}

void RBullet3::ShowRed3()
{
	setfillcolor(RED);
	solidcircle(m_nRow3, m_nCol3, 5);
}


void RBullet3::ShowClear3()				// ¸²¸Ç×Óµ¯
{
	setfillcolor(WHITE);
	solidcircle(m_nRow3, m_nCol3, 2);
}

void RBullet3::MoveDown3()
{
	m_nCol3 += 10;
}

RBullet3::RBullet3(int nRow3, int nCol3)
{
	m_nRow3 = nRow3;
	m_nCol3 = nCol3;
}



void RBullet4::MoveUp4()
{
	m_nCol4 -= 10;
	m_nRow4 -= 3;
}

void RBullet4::ShowRed4()
{
	setfillcolor(RED);
	solidcircle(m_nRow4, m_nCol4, 5);
}


void RBullet4::ShowClear4()				// ¸²¸Ç×Óµ¯
{
	setfillcolor(WHITE);
	solidcircle(m_nRow4, m_nCol4, 2);
}

void RBullet4::MoveDown4()
{
	m_nCol4 += 10;
}

RBullet4::RBullet4(int nRow4, int nCol4)
{
	m_nRow4 = nRow4;
	m_nCol4 = nCol4;
}






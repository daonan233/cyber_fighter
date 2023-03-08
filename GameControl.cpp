#include "GameControl.h"
#include "easyx.h"
#include "Control.h"

CGameControl::CGameControl()
{
	m_nScore = 0;
}

CGameControl::~CGameControl()
{
}

void CGameControl::ShowScore()
{
	TCHAR scoretext[50];
	setfillcolor(BLACK);
	solidrectangle(0, 0, 100, 50);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(50, 30, _T("»ªÎÄ²ÊÔÆ"));
	swprintf_s(scoretext, _T("%d"), m_nScore);
	outtextxy(0, 0, scoretext);
}
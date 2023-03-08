//////////////////////////////////////////////
// �������ƣ��ɻ���ս
// �������ߣ�C++20��ʵ��С��
// ���뻷����Visual Studio 2022 + EasyX_20190219(beta)
// ����޸ģ�2022-11-2
#pragma comment(lib, "WINMM.LIB")
#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <time.h>
#include "Enemy.h"
#include "Ship.h"
#include "Bullet.h"
#include "control.h"
#include "view.h"
#include "GameRole.h"

int main()
{
	srand((unsigned)time(NULL));
	initgraph(GAMEWIDTH, GAMEHIGHT);

	int nSign = 1;
	bool flag = true;
		while (nSign != -1)
		{
			InitGame();
			GetNewShip();
			if (flag) {
				for (int i = 0; i < 5; i++) {
					GetNewEnemy(i);
				}
				flag = false;
			}
			GetNewSmallEnemy();
			mygamecontrol.m_nScore = 0;
			RoleVector.push_back(&myship);
			for (int i = 0; i < 5; i++)
				RoleVector.push_back(&myenemy[i]);
			RoleVector.push_back(&mysmallenemy);

			while (nSign > 0)
			{
				nSign = HandleGameOver();
				GetOrder();							// ��ȡ����ָ��
				ShowInPut();						// ����ǰ�ڸǷɴ�
				DealInPut();						// �������
				EnemyMove();						// �л��ƶ�
				// ������Ϸ������ɫ
				for (size_t i = 0; i < RoleVector.size(); i++)
				{
					RoleVector[i]->ShowClearLife();
					RoleVector[i]->ShowLife();
					RoleVector[i]->ShowClear();
					RoleVector[i]->Show();
					RoleVector[i]->ShowBoom();
				}
				ShowBullet();						// ��ʾ�ɴ����л��ӵ�
				mygamecontrol.ShowScore();			// ��ʾ����

				MakeEnemyBullet();					// �����л��ӵ�
				DeleteMemory();						// �ͷ��ڴ�
				IsEnenmyHurt();						// �жϵл��Ƿ��е�
				IsShipHurt();						// �жϷɴ��Ƿ��е�
				SmallHitShip();						// �ж�С�л��Ƿ�ײ���ɴ�
				IsBullertHitSmall();				// С�л��Ƿ񱻻���
				isHasBeenEated();
				HandleBoom();                       // ����ը״̬
				nSign = HandleGameOver();
				HpSleep(10);						// ��ʱ
			}

			RoleVector.pop_back();
			RoleVector.pop_back();
			RoleVector.pop_back();
			nSign = 1;

		}
	closegraph();
	return 0;
}
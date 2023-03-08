//////////////////////////////////////////////
// 程序名称：飞机大战
// 程序作者：C++20班实践小组
// 编译环境：Visual Studio 2022 + EasyX_20190219(beta)
// 最后修改：2022-11-2
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
				GetOrder();							// 获取键盘指令
				ShowInPut();						// 操作前掩盖飞船
				DealInPut();						// 处理操作
				EnemyMove();						// 敌机移动
				// 绘制游戏各个角色
				for (size_t i = 0; i < RoleVector.size(); i++)
				{
					RoleVector[i]->ShowClearLife();
					RoleVector[i]->ShowLife();
					RoleVector[i]->ShowClear();
					RoleVector[i]->Show();
					RoleVector[i]->ShowBoom();
				}
				ShowBullet();						// 显示飞船、敌机子弹
				mygamecontrol.ShowScore();			// 显示分数

				MakeEnemyBullet();					// 产生敌机子弹
				DeleteMemory();						// 释放内存
				IsEnenmyHurt();						// 判断敌机是否中弹
				IsShipHurt();						// 判断飞船是否中弹
				SmallHitShip();						// 判断小敌机是否撞到飞船
				IsBullertHitSmall();				// 小敌机是否被击中
				isHasBeenEated();
				HandleBoom();                       // 处理爆炸状态
				nSign = HandleGameOver();
				HpSleep(10);						// 延时
			}

			RoleVector.pop_back();
			RoleVector.pop_back();
			RoleVector.pop_back();
			nSign = 1;

		}
	closegraph();
	return 0;
}
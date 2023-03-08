#pragma once
#include <vector>
#include <time.h>
#include <array>
#include "Ship.h"
#include "Bullet.h"
#include "SmallEnemy.h"
#include "GameControl.h"
#include "BloodBuff.h"

constexpr auto GAMEWIDTH = 1000;
constexpr auto GAMEHIGHT = 750;
using namespace std;

void InitGame();							// ��ʼ����Ϸ
bool GameOver();							// �ж���Ϸ����
void GetOrder();							// ��ȡ����ָ��
void EnemyMove();							// �ɴ��ƶ�
void MakeEnemyBullet();						// �����ɴ��ӵ�
void ShowBullet();							// ��ʾ�ɴ����л��ӵ�
void DeleteMemory();						// �ͷ��ڴ�
void IsEnenmyHurt();						// �жϵл��Ƿ��е�
void IsShipHurt();							// �жϷɴ��Ƿ��е�
void SmallHitShip();						// �ж�С�л��Ƿ�ײ���ɴ�
void GetNewSmallEnemy();					// �����С�л�
void GetNewEnemy(int i);					// ����µл�
void DealInPut();							// �������
bool IsBullertHitSmall();					// �ӵ��Ƿ����С�л�
bool SmallHitLow();							// С�л����ײ�
void HpSleep(int ms);						// ��ȷ��ʱ
int  HandleGameOver();						// ������Ϸ����
void HandleBoom();							// ����ը״̬
void GetNewBuff();                          //�����µ�Buff
void GetNewShip();
void isHasBeenEated();

class CShip;
class CEnemy;
class IMAGE;

enum Direction
{
	DOWN,
	Left,
	Right
};

extern IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;
extern vector<CBullet*> VectorBullets0;
extern vector<RBullet1*> VectorBullets1;
extern vector<RBullet2*> VectorBullets2;
extern vector<RBullet3*> VectorBullets3;
extern vector<RBullet4*> VectorBullets4;
extern vector<CBullet*> VectorEnenyBullets;
extern vector<CBullet*>::iterator Iter;
extern vector<RBullet1*>::iterator Iter1;
extern vector<RBullet2*>::iterator Iter2;
extern vector<RBullet3*>::iterator Iter3;
extern vector<RBullet4*>::iterator Iter4;
extern vector<CGameRole*> RoleVector;
extern BloodBuff bloodbuff;
extern std::array<int, 2> velocity;

extern CShip myship;				// �ɴ�λ�ã�Ѫ��
extern std::array<CEnemy, 5> myenemy;				// �л�λ�ã�Ѫ��
extern CSmallEnemy mysmallenemy;	// С�л�
extern CGameControl mygamecontrol;  // ��Ϸ����

enum GAMEINPUT
{
	UPINPUT = 0X1,
	DOWNINPUT = 0X2,
	LEFTINPUT = 0X4,
	RIGHTINPUT = 0X8,
	FIREINPUT = 0X10,
	ESCINPUT = 0X20,
	SPACEINPUT = 0X40,
	NOINPUT = 0X80
};

extern int myinput;

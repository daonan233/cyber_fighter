#pragma once
#include "Buff.h"
#include <graphics.h>
#include <easyx.h>


class BloodBuff :public Buff {

public:
	void showBuffImage()override;//��ʾbuffͼƬ
	void BuffGone()override;//BuffͼƬ���ڸ�
	void exeBuff(int blood, int bullet_num, CShip& plane)override;//ִ��buff���ݣ���Ѫ/���ӵ���(blood, bullet_num, &plane)
};
extern IMAGE buff1, buff;

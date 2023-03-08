#pragma once
#include "Buff.h"
#include <graphics.h>
#include <easyx.h>


class BloodBuff :public Buff {

public:
	void showBuffImage()override;//显示buff图片
	void BuffGone()override;//Buff图片被掩盖
	void exeBuff(int blood, int bullet_num, CShip& plane)override;//执行buff内容（加血/加子弹）(blood, bullet_num, &plane)
};
extern IMAGE buff1, buff;

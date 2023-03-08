#pragma once
#include <graphics.h>
#include <array>
#include "Ship.h"
class Buff {

public:
	int buff_pos_x{ 0 };
	int buff_pos_y{ 0 };//buff的位置变量

	bool hasReceived{ false };//buff有没有被飞机吃掉
	/*
	if(hasReceived){
	clearcircle(buff_pos_x,buff_pos_y,16)
	}
	*/

public:
	Buff() = default;

	Buff(int x, int y);

	virtual void showBuffImage();//显示buff图片


	virtual void exeBuff(int blood,int bullet_num, CShip& plane);//执行buff内容（加血/加子弹）(blood, bullet_num, &plane)

	void ImageMov(void (*visit)(int &, int &));//buff图片移动

	void ImageMov(void (*visit)(int&, int&, std::array<int, 2>& ), std::array<int, 2>& velocity);

	void isReceived(CShip& plane);//判断buff有没有被飞机吃掉

	[[nodiscard]] bool getHasReceived() const;


	virtual void BuffGone();//Buff图片被掩盖

	~Buff() = default;

};

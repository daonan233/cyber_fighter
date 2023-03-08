#pragma once
#include <graphics.h>
#include <array>
#include "Ship.h"
class Buff {

public:
	int buff_pos_x{ 0 };
	int buff_pos_y{ 0 };//buff��λ�ñ���

	bool hasReceived{ false };//buff��û�б��ɻ��Ե�
	/*
	if(hasReceived){
	clearcircle(buff_pos_x,buff_pos_y,16)
	}
	*/

public:
	Buff() = default;

	Buff(int x, int y);

	virtual void showBuffImage();//��ʾbuffͼƬ


	virtual void exeBuff(int blood,int bullet_num, CShip& plane);//ִ��buff���ݣ���Ѫ/���ӵ���(blood, bullet_num, &plane)

	void ImageMov(void (*visit)(int &, int &));//buffͼƬ�ƶ�

	void ImageMov(void (*visit)(int&, int&, std::array<int, 2>& ), std::array<int, 2>& velocity);

	void isReceived(CShip& plane);//�ж�buff��û�б��ɻ��Ե�

	[[nodiscard]] bool getHasReceived() const;


	virtual void BuffGone();//BuffͼƬ���ڸ�

	~Buff() = default;

};

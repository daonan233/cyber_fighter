#include "Buff.h"
#include <cmath>

Buff::Buff(int x, int y) :buff_pos_x{ x }, buff_pos_y{ y } {}

void Buff::showBuffImage() {

};//��ʾbuffͼƬ

void Buff::exeBuff(int blood, int bullet_num,CShip& plane) {

};//ִ��buff���ݣ���Ѫ/���ӵ���


void Buff::ImageMov(void(*visit)(int&, int&)) {
	visit(buff_pos_x, buff_pos_y);
}
void Buff::ImageMov(void(*visit)(int&, int&, std::array<int, 2>&), std::array<int, 2>& velocity) {
	visit(buff_pos_x, buff_pos_y, velocity);
}

//buffͼƬ�ƶ�
void Buff::isReceived(CShip& plane) {
	if (std::abs(buff_pos_x - plane.m_nRow) < 50 && std::abs(buff_pos_y - plane.m_nCol) < 50)
		hasReceived = true;
}

bool Buff::getHasReceived() const
{
	return hasReceived;
}
;//�ж�buff��û�б��ɻ��Ե�

void Buff::BuffGone() {
};//Buff���ڸ�
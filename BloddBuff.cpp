#include"BloodBuff.h"
#include "View.h"


void BloodBuff::showBuffImage() {
	putimage(buff_pos_x, buff_pos_y, &addBlood, SRCPAINT);
}
void BloodBuff::BuffGone() {
	putimage(buff_pos_x, buff_pos_y, &addBlood1, SRCAND);
}
void BloodBuff::exeBuff(int blood, int bullet_num, CShip& plane) {
	if (hasReceived) {
		plane.m_nLife += 100;
	}
}
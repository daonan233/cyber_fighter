#pragma once

class CBullet
{
public:
	int m_nRow;
	int m_nCol;

	CBullet(int nRow, int nCol);
	void MoveUp();
	void ShowYellow();
	void ShowBlue();
	void ShowClear();					// �����ӵ�
	void MoveDown();					// �ӵ�����
	void ShowRed();
};


class RBullet1 {
public:
	int m_nRow1;
	int m_nCol1;

	RBullet1(int nRow1, int nCol1);
	void MoveUp1();
	void ShowRed1();
	void ShowClear1();					// �����ӵ�
	void MoveDown1();					// �ӵ�����

};
class RBullet2 {
public:
	int m_nRow2;
	int m_nCol2;
	RBullet2(int nRow2, int nCol2);
	void MoveUp2();
	void ShowRed2();
	void ShowClear2();					// �����ӵ�
	void MoveDown2();					// �ӵ�����

};
class RBullet3 {
public:
	int m_nRow3;
	int m_nCol3;
	RBullet3(int nRow3, int nCol3);
	void MoveUp3();
	void ShowRed3();
	void ShowClear3();					// �����ӵ�
	void MoveDown3();					// �ӵ�����

};
class RBullet4 {
public:
	int m_nRow4;
	int m_nCol4;
	RBullet4(int nRow4, int nCol4);
	void MoveUp4();
	void ShowRed4();
	void ShowClear4();					// �����ӵ�
	void MoveDown4();					// �ӵ�����

};
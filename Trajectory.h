#pragma once
#include <array>
#include "Control.h"
#include "View.h"

void visit1(int& x, int& y, std::array<int, 2>& velocity) {
	x += velocity[0];
	y += velocity[1];
	if (x >= GAMEWIDTH || x <= 0)
		velocity[0] = -velocity[0];
	if (y >= GAMEHIGHT || y <= 0)
		velocity[1] = -velocity[1];
}
void visit2(int& x, int& y) {
	y += 3;
}
void visit3(int& x, int& y, std::array<int, 2>& velocity) {
	x += velocity[0];
	y += velocity[1];
	if (x <= 0 || x >= GAMEWIDTH)
		velocity[0] = -velocity[0];
}

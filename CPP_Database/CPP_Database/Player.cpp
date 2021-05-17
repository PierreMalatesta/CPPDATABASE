#include "Player.h"
#include <iostream>
#include <string.h>

Player::Player(const char* _name, unsigned int_highscore)
{
	strcpy_s(this->name, MaxNameLength, _name);
	this->highScore = highScore;


}

void Player::Draw()
{
	std::cout << name << ", " << highScore << std::endl;
}

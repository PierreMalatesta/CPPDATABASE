#include <iostream>
#include <string.h>
#include "Player.h"
#include "iostreamutils.h"

Player::Player(const char* _name, unsigned int_highscore)
{
	strcpy_s(this->name, MaxNameLength, _name);
	this->highScore = highScore;


}

void Player::Draw()
{
	std::cout << highScore  << ", " << name << std::endl;
}

bool Player::LoadFromConsole()
{
	cinclear();	//Clear pending input & error flags

	std::cout << "Enter player name>";
	std::cin >> name;
	std::cout << "Enter player score>";
	std::cin >> highScore;

	if (highScore > MaxScore)
		highScore = MaxScore;

	return true;
}

bool Player::operator<(const Player& other)
{
	return (highScore < other.highScore);
}

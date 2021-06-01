#pragma once


class Player
{
public:
	static const unsigned int MaxScore = 10000;
	static const unsigned int MaxNameLength = 50;

	Player(const char* _name = "", unsigned int highscore = 0);

	unsigned int GetHighScore() const { return highScore; }
	const char* GetName() const { return name; }

	void Draw();
	bool LoadFromConsole();

	//compare by highscore 
	bool operator<(const Player& other); 

private:
	char name[MaxNameLength] = {};
	unsigned int highScore = 0;
};


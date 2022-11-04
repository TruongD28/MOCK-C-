#include "User.h"

User::User()
{
	Win = 0;
	Lose = 0;
	Draw = 0;
}

User::~User()
{
}

void User::setName(string& name)
{
	Name = name;
}

string User::getName()
{
	return Name;
}

void User::setWin(const int& win)
{
	Win = win;
}

int User::getWin()
{
	return Win;
}

void User::setLose(const int& lose)
{
	Lose = lose;
}

int User::getLose()
{
	return Lose;
}

void User::setDraw(const int& draw)
{
	Draw = draw;
}

int User::getDraw()
{
	return Draw;
}

void User::ShowInfo()
{
	cout << " Name: " << getName() << endl;
	cout << " Win: " << getWin() << endl;
	cout << " Lose: " << getLose() << endl;
	cout << " Draw: " << getDraw() << endl;
}

float User::getWinRate()
{
	float Winrate, sum, total;

	sum = (float)Win + (float)Lose + (float)Draw;
	total = (float)Win - (float)Lose;
	if (total > 0)
	{
		Winrate = total / sum ;
	}
	else if ( total == 0 )
	{
		Winrate = 50 ;
	}
	else if (total < 0)
	{
		Winrate = 0;
	}
	return Winrate;
}

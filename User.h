#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;
class User
{
	string Name;
	int Win, Lose, Draw;
public:
	User();
	~User();
	void setName(string&);
	string getName();

	void setWin(const int&);
	int getWin();

	void setLose(const int&);
	int getLose();

	void setDraw(const int&);
	int getDraw();

	float getWinRate();

	void ShowInfo();
};

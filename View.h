#pragma once
#include"Windows.h"
using namespace std;
class View
{
public:
	View();
	~View();

	static void DisplayBoard(const int& size);										// Display the board
	static void DisplayOX(const int& row, const int& col, const char& OX);			// Display char XO on screen
};

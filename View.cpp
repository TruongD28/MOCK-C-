#include "View.h"

View::View()
{
}

View::~View()
{
}

void View::DisplayBoard(const int& size)
{
	for (int i = 0; i < 2 * size; i++) 
	{
		for (int j = 0; j <= 2 * size; j++)
		{
			Windows::gotoXY(j, i);
			if (i % 2 == 0)			
			{
				if (j % 2 == 0)
				{
					cout << "|";
				}
				else
				{
					cout << "  ";
				}
			}
			else
			{
				cout << "--";
			}

		}
	}
}

void View::DisplayOX(const int& row, const int& col, const char& OX)
{
	Windows::gotoXY(2 * col + 1, 2 * row);	
	cout << OX;
}
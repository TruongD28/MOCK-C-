#include "UI.h"
UI::UI() 
{
	screenMain();
}
UI::~UI() {}

void UI::screenMain()
{
	int chose;
	while (run)
	{
		system("cls");
		cout << "1. Add player." << endl;
		cout << "2. Start game." << endl;
		cout << "3. Replay." << endl;
		cout << "4. Show player info." << endl;
		cout << "5. Export player Info to ini" << endl;
		cout << "6. Export all player Info to ini " << endl;
		cout << "7. Find enemy by winrate" << endl;
		cout << "0. Exit." << endl;
		do
		{
			cin >> chose;
			if (chose > 7 || chose < 0)
			{
				cout << "Type again.";
			}
		} while (chose > 7 || chose < 0);

		switch (chose)
		{
		case ADDPLAYER:
			system("cls");
			control.CreatePlayer();
			system("pause");
			break;
		case STARTGAME:
			system("cls");
			control.StartGame();
			system("pause");
			break;
		case REPLAY:
			system("cls");
			control.Replay();
			system("pause");
			break;
		case SHOWPLAYERINFO:
			system("cls");
			control.ShowPlayer();
			system("pause");
			break;
		case EXPORTINFO:
			system("cls");
			control.exportInfo();
			system("pause");
			break;
		case EXPORTALLINFO:
			system("cls");
			control.findAllInfo();
			system("pause");
			break;
		case FINDENEMY:
			system("cls");
			control.findEnemy();
			system("pause");
			break;
		case EXIT:
			run = false;
			break;
		}
	} 
}

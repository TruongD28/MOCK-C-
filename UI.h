#pragma once
#include"Controller.h"

enum action
{
	ADDPLAYER = 1,
	STARTGAME = 2,
	REPLAY = 3,
	SHOWPLAYERINFO = 4,
	EXPORTINFO = 5,
	EXPORTALLINFO = 6,
	FINDENEMY = 7,
	EXIT =0

};
class UI
{
private:
	Controller control;
	bool run = true;
public:
	UI();
	~UI();
	void screenMain();
};

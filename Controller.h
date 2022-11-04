#pragma once
#include"Model.h"
#include"View.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "User.h"
using namespace std;

class Controller
{

	Model model;			// use this object to member of model
	View view;				// use this object to member of view
public:
	Controller();
	~Controller();

	void StartGame();
	void CreatePlayer();
	void writePlayerInfo();
	void ShowPlayer();
	bool FindPlayer(const string&);
	bool CheckPoint(int& row, int& col);				// check whether this point available or not
	char CheckResult(int& row, int& col, char& XO);		// check whether 1 of 2 play win or not
	void UpdateIndex(const string& name, const string& res, const int& i); //update data about match of user
	void ChangeTurn(char&);
	void Replay();
	void exportInfo();
	void findAllInfo();
	void findEnemy();

};
#pragma once
#include"User.h"

typedef struct
{
	int size, row, col;
	char XO;
}data1;

class Model
{
private:
	int gameID;
	int size;							// size board
	map<string, User> UserList;			// list player
	int count;							// counting number of turn was played
	vector<vector <char>> Point;		// 2 dimension vector
	map<int, vector<vector<char>>> gameList;	
	map<int, vector<data1>> Replay;				
public:
	Model();
	~Model();

	int getSize();
	void setSize(int&);													// Set size board
	void AddUser(User&);												// add user
	map<string, User>& getUser();										// get user
	int getCount();
	void addPoint(const int& row, const int& col, const char OX);		// add char X or char O to board on (x = row, y = col) 
	vector<vector<char>>& getPoint();									// get char on (x = row, y = col) 
	void Init2DVector(int& size);										//void showUserList();
	void setgameID(const int&);
	int getgameID();
	map<int, vector<vector<char>>>& getgameList();
	map<int, vector<data1>>& getReplay();
};


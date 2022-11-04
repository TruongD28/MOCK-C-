#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

int Model::getSize()
{
	return size;
}

void Model::setSize(int& _size)
{
	size = _size;
}

void Model::AddUser(User& user)
{
	if (UserList.count(user.getName()) != 0)
	{
		cout << "Existed User.";
	}
	else
	{
		UserList[user.getName()] = user;
	}
}


map<string, User>& Model::getUser()
{
	return UserList;
}

int Model::getCount()
{
	return count;
}

void Model::addPoint(const int& row, const int& col, const char OX)
{
	Point[row][col] = OX;
	count++;
}

vector<vector<char>>& Model::getPoint()
{
	return Point;
}

void Model::Init2DVector(int& size) 
{
	vector<vector<char>> init2Dvector(size, vector<char>(size, ' '));
	Point = init2Dvector;
}

void Model::setgameID(const int& gameID)
{
	this->gameID = gameID;
}

int Model::getgameID()
{
	return gameID;
}

map<int, vector<data1>>& Model::getReplay()
{
	return Replay;  // getReplay 
}

map<int, vector<vector<char>>>& Model::getgameList()
{
	return gameList;
}
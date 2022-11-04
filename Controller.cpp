#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::StartGame()
{
    int row, col;
    int size;
    char Turn = 'X';
    string pName1, pName2;
    bool mEnd = false;


    data1 structReplay;
    vector<data1> vReplay;

    int GAMEID;
    cout << " Enter game ID: ";
    cin >> GAMEID;

    if (model.getgameList().count(GAMEID) != 0)
    {
        cout << "Game ID existed.";
        return;
    }
    else
    {
        model.setgameID(GAMEID);
    }


    cout << "Enter player 1: ";
    getline(cin >> ws, pName1);
    if (FindPlayer(pName1) == false)
    {
        cout << "Player not found.";
        return;
    }

    cout << "Enter player 2: ";
    getline(cin >> ws, pName2);
    if (FindPlayer(pName2) == false)
    {
        cout << "Player not found.";
        return;
    }

    cout << "Size of the board: ";
    cin >> size;

    structReplay.size = size;

    system("cls");
    model.setSize(size); 
    model.Init2DVector(size);
    view.DisplayBoard(size); 


    INPUT_RECORD ir[128];
    HANDLE       hStdInput = NULL;
    HANDLE       hStdOutput = NULL;
    HANDLE       hEvent = NULL;
    DWORD        nRead;
    COORD        xy;

    hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    FlushConsoleInputBuffer(hStdInput);
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE handles[2] = { hEvent, hStdInput };
    while (WaitForMultipleObjects(2, handles, FALSE, INFINITE))
    {
        ReadConsoleInput(hStdInput, ir, 128, &nRead);
        for (size_t i = 0; i < nRead; i++)
        {
            xy.X = 0, xy.Y = 1;
            SetConsoleCursorPosition(hStdOutput, xy);
            col = ir[i].Event.MouseEvent.dwMousePosition.X / 2;
            row = ir[i].Event.MouseEvent.dwMousePosition.Y / 2;
            if (ir[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                if (!CheckPoint(row, col))
                {
                    Windows::gotoXY(50, 0);
                    cout << "Invalid.";
                }
                else
                {
                    model.addPoint(row, col, Turn);
                    view.DisplayOX(row, col, Turn);

                    structReplay.row = row;
                    structReplay.col = col;
                    structReplay.XO = Turn;
                    vReplay.push_back(structReplay);
                    model.getReplay()[GAMEID] = vReplay;

                    if (CheckResult(row, col, Turn) == 'X')
                    {
                        system("cls");
                        Windows::gotoXY(50, 0);
                        cout << "Player 1 win";
                        int i_win = model.getUser()[pName1].getWin();
                        UpdateIndex(pName1, "win", i_win + 1);
                        int i_lose = model.getUser()[pName2].getLose();
                        UpdateIndex(pName2, "lose", i_lose + 1);
                        mEnd = true;

                    }
                    else if (CheckResult(row, col, Turn) == 'O')
                    {
                        system("cls");
                        Windows::gotoXY(50, 0);
                        cout << "Player 2 win";
                        int i_win = model.getUser()[pName2].getWin();
                        UpdateIndex(pName2, "win", i_win + 1);
                        int i_lose = model.getUser()[pName1].getLose();
                        UpdateIndex(pName1, "lose", i_lose + 1);
                        mEnd = true;
                    }
                    else if (CheckResult(row, col, Turn) == 'D')
                    {
                        system("cls");
                        Windows::gotoXY(50, 0);
                        cout << "DRAW";
                        int i_draw1 = model.getUser()[pName1].getWin();
                        UpdateIndex(pName1, "draw", i_draw1 + 1);
                        int i_draw2 = model.getUser()[pName2].getLose();
                        UpdateIndex(pName2, "draw", i_draw2 + 1);
                        mEnd = true;
                    }
                    if (mEnd)
                    {

                        model.getgameList()[GAMEID] = model.getPoint();
                        Windows::gotoXY(0, 0);
                        return;
                    }

                    ChangeTurn(Turn);
                }

            }
        }
    };
}

void Controller::CreatePlayer()
{
    string name;
    cout << "Enter user name: ";
    getline(cin >> ws, name);
    User user;
    user.setName(name);
    model.AddUser(user);
    /*
    fstream file;
    file.open(name + ".ini", ios::out);
    file << "Name: " << user.getName() << endl;
    file << "Win: " << user.getWin() << endl;
    file << "Lose: " << user.getLose() << endl;
    file << "Draw: " << user.getDraw() << endl;
    file.close();
    cout << "Da xuat thong tin ra file name: " << name << ".ini" << endl;
    */
}

void Controller::ShowPlayer()
{
    string name;
    cout << "Enter username: ";
    getline(cin >> ws, name);
    model.getUser()[name].ShowInfo();
    system("pause");
}

bool Controller::FindPlayer(const string& name)
{
    if (model.getUser().count(name) != 0) return true;
    else return false;
}

bool Controller::CheckPoint(int& row, int& col)
{
    if (row > model.getSize() || col > model.getSize()) return false;
    else if (model.getPoint()[row][col] != ' ') return false;
    else return true;
}

char Controller::CheckResult(int& row, int& col, char& turn)
{
    vector<vector<char>> check = model.getPoint();
    int continuous = 1;
    int i = 1;
    // check row
    if (model.getSize() * model.getSize() != model.getCount()) // nếu size bàn cờ = số ô thì kết quả là hòa
    {
        while (col + i < model.getSize())
        {
            if (check[row][col + i] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                break;
            }

        }

        while (col - i >= 0)
        {
            if (check[row][col - i] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                continuous = 1;
                break;
            }
        }

        //check column
        while (row + i < model.getSize())
        {
            if (check[row + i][col] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                break;
            }

        }

        while (row - i >= 0)
        {
            if (check[row - i][col] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                continuous = 1;
                break;
            }
        }
        //check cross '\'
        while (row + i < model.getSize() && col + i < model.getSize())
        {
            if (check[row + i][col + i] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                break;
            }

        }

        while (row - i >= 0 && col - i >= 0)
        {
            if (check[row - i][col - i] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                continuous = 1;
                break;
            }
        }
        //check cross '/'
        while (row - i >= 0 && col + i < model.getSize())
        {
            if (check[row - i][col + i] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                break;
            }

        }

        while (row + i < model.getSize() && col - i >= 0)
        {
            if (check[row + i][col - i] == turn)
            {
                continuous++;
                if (continuous == 5) return turn;
                i++;
            }
            else
            {
                i = 1;
                continuous = 1;
                break;
            }
        }

    }
    else if (model.getSize() * model.getSize() == model.getCount()) return 'D';

}

void Controller::UpdateIndex(const string& name, const string& res, const int& i)
{
    if (res == "win")
    {
        model.getUser()[name].setWin(i);
    }
    else if (res == "lose")
    {
        model.getUser()[name].setLose(i);
    }
    else if (res == "draw")
    {
        model.getUser()[name].setDraw(i);
    }

}

void Controller::ChangeTurn(char& turn)
{
    if (turn == 'X') { turn = 'O'; }
    else if (turn == 'O') { turn = 'X'; }
}

void Controller::Replay()
{
    int ID;
    cout << "Enter game ID: ";
    cin >> ID;

    int chose;
    if (model.getgameList().count(ID) == 0)
    {
        cout << "Game ID is not existed.";
    }
    else
    {
        system("cls");
        view.DisplayBoard(model.getReplay()[ID].begin()->size);
        for (auto i : model.getReplay()[ID])
        {
            view.DisplayOX(i.row, i.col, i.XO);
            Sleep(500);
        }
        Windows::gotoXY(50, 0);
        system("pause");
    }
    return;
}

void Controller::exportInfo()
{
    string _name;
    cout << "Nhap ten nguoi choi can xuat thong tin: " << endl;
    fflush(stdin);
    getline(cin >> ws, _name);
    if (model.getUser().count(_name) == 1)
    {
        User tPlayer = model.getUser().find(_name)->second;
        fstream file;
        file.open(_name + ".ini", ios::out);
        file << "Name: " << tPlayer.getName() << endl;
        file << "Win: " << tPlayer.getWin() << endl;
        file << "Lose: " << tPlayer.getLose() << endl;
        file << "Draw: " << tPlayer.getDraw() << endl;
        file.close();
        cout << "Da xuat thong tin ra file name: " << _name << ".ini" << endl;

    }
    else
    {
        cout << "Nguoi choi khong ton tai" << endl;
    }

}
void Controller::findAllInfo()
{
    int count = 1;
    fstream file;
    file.open("Listplayer.ini", ios::out);
    for (auto i = model.getUser().begin(); i != model.getUser().end(); i++)
    {
        file << "Player" << count << endl;
        file << "Name: " << i->second.getName() << endl;
        file << "Win: " << i->second.getWin() << endl;
        file << "Lose: " << i->second.getLose() << endl;
        file << "Draw: " << i->second.getDraw() << endl;
        count++;
    }
    cout << "Da hoan thanh xuat thong tin nguoi choi. " << endl;
    file.close();

}
void Controller::findEnemy()
{
    vector<float> ListWinrate;
    for (auto i = model.getUser().begin(); i != model.getUser().end(); i++)
    {
        ListWinrate.push_back(i->second.getWinRate());
    }
    sort(ListWinrate.begin(), ListWinrate.end());
    string _name;
    cout << "Nhap ten nguoi choi can tim doi thu: ";
    fflush(stdin);
    getline(cin >> ws, _name);
    if (model.getUser().count(_name) == 1)
    {
        User founedPlayer = model.getUser().find(_name)->second;
        for (int i = 0; i < ListWinrate.size(); i++)
        {
            if (ListWinrate[i] == founedPlayer.getWinRate())
                if (i == ListWinrate.size() - 1)
                {
                    for (auto j = model.getUser().begin(); j != model.getUser().end(); j++)
                    {
                        if (j->second.getWinRate() == ListWinrate[i - 1])
                        {
                            int chonxuatfile;

                            cout << "Thong tin nguoi can tim doi thu: " << endl;
                            cout << "Name: " << founedPlayer.getName() << endl;
                            cout << "Win: " << founedPlayer.getWin() << endl;
                            cout << "Lose: " << founedPlayer.getLose() << endl;
                            cout << "Draw: " << founedPlayer.getDraw() << endl;
                            cout << "Winrate: " << founedPlayer.getWinRate() * 100 << "%" << endl;

                            cout << "Thong tin cua doi thu" << endl;
                            cout << "Name: " << j->second.getName() << endl;
                            cout << "Win: " << j->second.getWin() << endl;
                            cout << "Lose: " << j->second.getLose() << endl;
                            cout << "Draw: " << j->second.getDraw() << endl;
                            cout << "Winrate: " << j->second.getWinRate() * 100 << "%" << endl;

                            cout << "Ban co muon xuat thong tin doi thu ra file ini khong?" << endl;
                            cout << "1. Co" << endl;
                            cout << "2. Khong" << endl;
                            cin >> chonxuatfile;
                            if (chonxuatfile == 1) {
                                fstream file;
                                file.open("Findenemy.ini", ios::out);
                                file << "Thong tin nguoi can tim doi thu: " << endl;
                                file << "Name: " << founedPlayer.getName() << endl;
                                file << "Win: " << founedPlayer.getWin() << endl;
                                file << "Lose: " << founedPlayer.getLose() << endl;
                                file << "Draw: " << founedPlayer.getDraw() << endl;
                                file << "Winrate: " << founedPlayer.getWinRate() * 100 << "%" << endl;

                                file << "Thong tin cua doi thu" << endl;
                                file << "Name: " << j->second.getName() << endl;
                                file << "Win: " << j->second.getWin() << endl;
                                file << "Lose: " << j->second.getLose() << endl;
                                file << "Draw: " << j->second.getDraw() << endl;
                                file << "Winrate: " << founedPlayer.getWinRate() * 100 << "%" << endl;

                                file.close();
                            }
                            else
                            {
                                return;
                            }

                        }
                        else
                        {
                            for (auto j = model.getUser().begin(); j != model.getUser().end(); j++)
                            {
                                if (j->second.getWinRate() == ListWinrate[i + 1])
                                {
                                    if (j->first != founedPlayer.getName())
                                    {
                                        int chonxuatfile;
                                        cout << "Thong tin nguoi can tim doi thu: " << endl;
                                        cout << "Name: " << founedPlayer.getName() << endl;
                                        cout << "Win: " << founedPlayer.getWin() << endl;
                                        cout << "Lose: " << founedPlayer.getLose() << endl;
                                        cout << "Draw: " << founedPlayer.getDraw() << endl;

                                        cout << "Thong tin cua doi thu" << endl;
                                        cout << "Name: " << j->second.getName() << endl;
                                        cout << "Win: " << j->second.getWin() << endl;
                                        cout << "Lose: " << j->second.getLose() << endl;
                                        cout << "Draw: " << j->second.getDraw() << endl;

                                        cout << "Ban co muon xuat thong tin doi thu ra file ini khong?" << endl;
                                        cout << "1. Co" << endl;
                                        cout << "2. Khong" << endl;
                                        cin >> chonxuatfile;
                                        if (chonxuatfile == 1) {
                                            fstream file;
                                            file.open("Findenemy.ini", ios::out);
                                            file << "Thong tin nguoi can tim doi thu: " << endl;
                                            file << "Name: " << founedPlayer.getName() << endl;
                                            file << "Win: " << founedPlayer.getWin() << endl;
                                            file << "Lose: " << founedPlayer.getLose() << endl;
                                            file << "Draw: " << founedPlayer.getDraw() << endl;

                                            file << "Thong tin cua doi thu" << endl;
                                            file << "Name: " << j->second.getName() << endl;
                                            file << "Win: " << j->second.getWin() << endl;
                                            file << "Lose: " << j->second.getLose() << endl;
                                            file << "Draw: " << j->second.getDraw() << endl;
                                            file.close();
                                        }
                                        else
                                        {
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
        }
    }
    else
    {
        cout << "Nguoi choi khong ton tai" << endl;
    }

}

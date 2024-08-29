#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <unistd.h> //for using sleep in making sandclock
#include <windows.h>//coloring console and text
#include <fstream>  //Working with files
#include <string>

using namespace std;

int score, moveCnt, lvl;
struct Table
{
    int n;
    bool chComb;
};

Table GameTab[10][10];

struct Player
{
    int mxScore;
    int moves;
    string playerID;
};

int s = 0;
Player ldrBrd[100];
ofstream leaderBoard("leaderboard.txt", ios::app);

void bubble_sort()
{
    for (int i = 1; i < s; i++)
        for (int j = 1; j < s - i; j++)
        {
            if (ldrBrd[j].mxScore > ldrBrd[j+1].mxScore)
                swap(ldrBrd[j], ldrBrd[j + 1]);
            else if(ldrBrd[j].mxScore == ldrBrd[j+1].mxScore)
            {
                if(ldrBrd[j].moves < ldrBrd[j+1].moves)
                    swap(ldrBrd[j], ldrBrd[j + 1]);
            }
        }

}
//going back to menue **********
void SandClock(int n)
{
    system("cls");
    int sand = n/2 - 1;
    for(int i = 0; i <= sand; i++)
    {
        system("cls");
        cout << "\n\n   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        cout << "\n   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        cout << "\n";
        for(int j = 0; j < sand; j++)
        {
            for(int k = 0; k <= j + 3; k++)
                cout << " ";
            cout << "*";
            if(j < i)
            {
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << " ";
            }
            else
            {
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << ".";
            }
            cout << "*\n";
        }
        for(int j = 0; j <= sand; j++)
            cout << " ";
        cout << "   *\n";
        for(int j = sand - 1; j >= 0; j--)
        {
            for(int k = 0; k <= j + 3; k++)
                cout << " ";
            cout << "*";
            if(j >= i)
            {
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << " ";
            }
            else
            {
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << ".";
            }
            cout << "*\n";
        }
        cout << "   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        cout << "\n   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        if(i != 0)
            sleep(1);
    }
}

bool WiningCond()
{
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl; j++)
        {
            if(GameTab[i][j].n == 2048)
                return true;
            else if(lvl == 3 && GameTab[i][j].n == 1024)
                return true;
        }
    }
    return false;
}

bool LosingCond()
{
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl; j++)
        {
            if(GameTab[i][j].n == 0 || GameTab[i][j].n == 2048)
                return false;
        }
    }
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl - 1; j++)
        {
            if(GameTab[i][j].n == GameTab[i][j + 1].n)
                return false;
        }
    }
    for(int i = 0; i < lvl - 1; i++)
    {
        for(int j = 0; j < lvl; j++)
        {
            if(GameTab[i][j].n == GameTab[i+1][j].n)
                return false;
        }
    }
    return true;
}

void HalfWay(string name)
{
    cout << "\nDear " << name << ", Your Final Score is " << score << "With " << moveCnt << " Moves!";
    cout << "\nGreat Job!\n";
}

//the function that deletes and prints the table everytime
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//coloring console

void IntToBlock(int n)
{
    switch (n)
    {
        case 0:
            cout << "    "; break;
        case 2:
        {
            SetConsoleTextAttribute(hConsole, 240);
            cout << " 2  "; break;
        }
        case 4:
        {
            SetConsoleTextAttribute(hConsole, 224);
            cout << " 4  "; break;
        }
        case 8:
        {
            SetConsoleTextAttribute(hConsole, 143);
            cout << " 8  "; break;
        }
        case 16:
        {
            SetConsoleTextAttribute(hConsole, 159);
            cout << " 16 "; break;
        }
        case 32:
        {
            SetConsoleTextAttribute(hConsole, 175);
            cout << " 32 "; break;
        }
        case 64:
        {
            SetConsoleTextAttribute(hConsole, 47);
            cout << " 64 "; break;
        }
        case 128:
        {
            SetConsoleTextAttribute(hConsole, 31);
            cout << "128 "; break;
        }
        case 256:
        {
            SetConsoleTextAttribute(hConsole, 95);
            cout << "256 "; break;
        }
        case 512:
        {
            SetConsoleTextAttribute(hConsole, 223);
            cout << "512 "; break;
        }
        case 1024:
        {
            SetConsoleTextAttribute(hConsole, 207);
            cout << "1024"; break;
        }
        case 2048:
        {
            SetConsoleTextAttribute(hConsole, 79);
            cout << "2048"; break;
        }
    }

}

void MakeTable()
{
    system("cls");
    for(int i = 0; i < 3*lvl; i++)
    {
        if(i%3 == 0)
        {
            for(int j = 0; j < 6*lvl; j++)
            {
                if(j%6 == 0)
                    cout << "\u256D";
                else if(j%6 == 5)
                    cout << "\u256E";
                else
                    cout << "\u2500";
            }
        }
        else if(i%3 == 1)
        {
            for(int j = 0; j < 3*lvl; j++)
            {
                if(j%3 == 0 || j%3 == 2)
                    cout << "\u2502";
                else if(j%3 == 1)
                {
                    IntToBlock(GameTab[i/3][j/3].n);
                    SetConsoleTextAttribute(hConsole, 14);
                }
            }
        }
        else
        {
            for(int j = 0; j < 6*lvl; j++)
            {
                if(j%6 == 0)
                    cout << "\u2570";
                else if(j%6 == 5)
                    cout << "\u256F";
                else
                    cout << "\u2500";
            }
        }
        cout << "\n";
    }
    SetConsoleTextAttribute(hConsole, 10);
    cout << "SCORE : " << score;
    cout << "\n" << moveCnt << " moves";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\n\nPress 'q' to exit the game.\n";
}

//Game movements and the results
//*****************************
int CombBlocks(int row1, int col1, int row2, int col2)
{
    GameTab[row1][col1].n *= 2;
    GameTab[row1][col1].chComb = true;
    GameTab[row2][col2].n = 0;
    return GameTab[row1][col1].n;
}

void AddRndBlock()
{
    //peydakardan khanehaye khali
    int emptyBlocks[lvl*lvl], sz = 0;
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl; j++)
        {
            if(GameTab[i][j].n == 0)
            {
                emptyBlocks[sz] = i*lvl+j;
                sz++;
            }
        }
    }
    int newBlockPos = emptyBlocks[rand()%sz], nBlockNum = rand()%4;
    if(nBlockNum == 0)
        GameTab[newBlockPos/lvl][newBlockPos%lvl].n = 4;
    else
        GameTab[newBlockPos/lvl][newBlockPos%lvl].n = 2;
}

void MoveUp()
{
    bool blcMoved = false;
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl; j++)
            GameTab[j][i].chComb = false;
        for(int j = 1; j < lvl; j++)
        {
            if(GameTab[j][i].n != 0)
            {
                int k = j - 1;
                while(GameTab[k][i].n == 0 && k >= 0)
                {
                    blcMoved = true;
                    swap(GameTab[k + 1][i], GameTab[k][i]);
                    k--;
                }
                if(GameTab[k+1][i].n == GameTab[k][i].n && GameTab[k][i].chComb == false)
                {
                    blcMoved = true;
                    score += CombBlocks(k, i, k+1, i);
                }
            }
        }
    }
    if(blcMoved == true)
    {
        AddRndBlock();
        moveCnt++;
    }
    MakeTable();
}

void MoveDown()
{
    bool blcMoved = false;
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl; j++)
            GameTab[j][i].chComb = false;
        for(int j = lvl - 2; j >= 0; j--)
        {
            if(GameTab[j][i].n != 0)
            {
                int k = j + 1;
                while(GameTab[k][i].n == 0 && k < lvl)
                {
                    blcMoved = true;
                    swap(GameTab[k - 1][i], GameTab[k][i]);
                    k++;
                }
                if(GameTab[k-1][i].n == GameTab[k][i].n && GameTab[k][i].chComb == false)
                {
                    blcMoved = true;
                    score += CombBlocks(k, i, k - 1, i);
                }
            }
        }
    }
    if(blcMoved == true)
    {
        AddRndBlock();
        moveCnt++;
    }
    MakeTable();
}

void MoveRight()
{
    bool blcMoved = false;
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl; j++)
            GameTab[i][j].chComb = false;
        for(int j = lvl - 2; j >= 0; j--)
        {
            if(GameTab[i][j].n != 0)
            {
                int k = j + 1;
                while(GameTab[i][k].n == 0 && k < lvl)
                {
                    blcMoved = true;
                    swap(GameTab[i][k - 1], GameTab[i][k]);
                    k++;
                }
                if(GameTab[i][k - 1].n == GameTab[i][k].n && GameTab[i][k].chComb == false)
                {
                    blcMoved = true;
                    score += CombBlocks(i, k, i, k - 1);
                }
            }
        }
    }
    if(blcMoved == true)
    {
        AddRndBlock();
        moveCnt++;
    }
    MakeTable();
}

void MoveLeft()
{
    bool blcMoved = false;
    for(int i = 0; i < lvl; i++)
    {
        for(int j = 0; j < lvl - 1; j++)
            GameTab[i][j].chComb = false;
        for(int j = 1; j < lvl; j++)
        {
            if(GameTab[i][j].n != 0)
            {
                int k = j - 1;
                while(GameTab[i][k].n == 0 && k >= 0)
                {
                    blcMoved = true;
                    swap(GameTab[i][k + 1], GameTab[i][k]);
                    k--;
                }
                if(GameTab[i][k+1].n == GameTab[i][k].n && GameTab[i][k].chComb == false)
                {
                    blcMoved = true;
                    score += CombBlocks(i, k, i, k+1);
                }
            }
        }
    }
    if(blcMoved == true)
    {
        AddRndBlock();
        moveCnt++;
    }
    MakeTable();
}
//*****************************

//Playing process %%%%%%%%%%%%%%%%%%%
void Play(string name)
{
    char movement = '0';
    while(!WiningCond() && !LosingCond() && movement != 'q')
    {
        movement = getch();
        switch(movement)
        {
            case 'w':
                MoveUp(); break;
            case 'a':
                MoveLeft(); break;
            case 's':
                MoveDown(); break;
            case 'd':
                MoveRight(); break;
            case 'q':
                HalfWay(name); break;
            default:
                cout << "\nThis Movement Is Not Valid.";
        }
    }
    if(WiningCond())
    {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n";
        cout << "\u2551 YOU WON! \u2551\n";
        cout << "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Your Score is " << score << "With " << moveCnt << " Moves!";
    }
    else if(LosingCond())
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n";
        cout << "\u2551 YOU LOST:( \u2551\n";
        cout << "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Your Score is " << score << " So Far.\nBetter Luck Next Time.";
    }
    return;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Managing Menue options
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void NewGame(string name)
{
    for(int i = 0; i <= lvl; i++)
    {
        for(int j = 0; j <= lvl; j++)
            GameTab[i][j].n = 0;
    }
    //managing first pair of blocks///////
    int block1 = rand() % (lvl*lvl), block2 = rand() % (lvl*lvl - 1);
    int blc1 = (rand()%4 == 0)? 4 : 2, blc2 = (rand()%4 == 0)? 4 : 2;
    GameTab[block1/lvl][block1%lvl].n = blc1;
    if(block2 >= block1)
        block2++;
    GameTab[block2/lvl][block2%lvl].n = blc2;
    //////////////////////////////////////
    MakeTable();
    Play(name);
}

void LeaderBoard()
{
    ifstream leaderBoard("leaderboard.txt");
    string name;
    int score, moves, cnt = 0;
    while (leaderBoard >> name >> score >> moves)
    {
        cnt++;
        ldrBrd[cnt].playerID = name;
        ldrBrd[cnt].mxScore = score;
        ldrBrd[cnt].moves = moves;
    }
    //bubble_sort();
    cout << "#RANKING:\n";
    for (int i = 0; i <= s; i++)
    {
        SetConsoleTextAttribute(hConsole, i%15 + 1);
        cout << i << "- " << ldrBrd[i].playerID << " : " << ldrBrd[i].mxScore << " With " << ldrBrd[i].moves << " Moves.\n";
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void MakeMenue(){
    char opt = '0';
    while(opt != '3')
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 10);
        cout << "~~~~~~~~ WELCOME TO 2048! ~~~~~~~~\n";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "1\u2590 Press 1 For Starting a New Game.\n";
        cout << "2\u2590 Press 2 For Showing Leaderboard.\n";
        cout << "3\u2590 Press 3 In Case You Have Nothing To Do Here:)\n";
        opt = getch();
        while(opt != '1' && opt != '2' && opt != '3')
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "WARNING! ENTER A VALID NUMBER.\n";
            opt = getch();
        }
        SetConsoleTextAttribute(hConsole, 15);
        system("cls");
        if(opt == '1')
        {
            string name;
            score = 0, lvl = 0, moveCnt = 0;
            cout << "Enter Your Name: ";
            cin >> name;
            leaderBoard << name;
            cout << "Choose Your Level.(Please Give Me a Number From 3 to 10): \n";
            cout << "*In 3 Dimension Mode You Only Have to Reach 1024.\n";
            while(lvl < 3 || lvl > 10)
            {
                SetConsoleTextAttribute(hConsole, 15);
                cin >> lvl;
                system("cls");
                cout << "Enter Your Name: " << name;
                cout << "\nChoose Your Level.(Please Give Me a Number From 3 to 10): \n";
                cout << "*In 3 Dimension Mode You Only Have to Reach 1024.\n";
                SetConsoleTextAttribute(hConsole, 12);
                cout << "This Level Doesn't Exist.\nPlease Enter a Number From 3 to 10.\n";
            }
            SetConsoleTextAttribute(hConsole, 15);
            NewGame(name);
            leaderBoard << " " << score << " " << moveCnt << "\n";
        }
        else if(opt == '2')
        {
            system("cls");
            LeaderBoard();
        }
        else
        {
            cout << "Have a Nice Day!";
            return;
        }
        cout << "\nPress Any Key to Continue.\n";
        _getch();
        SandClock(9);
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    MakeMenue();
    leaderBoard.close();
}

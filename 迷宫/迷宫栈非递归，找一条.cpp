#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include"windows.h"

using namespace std;

struct Coord
{
    int x;
    int y;
    Coord(int xi = 0, int yi = 0):x(xi),y(yi){}
    Coord(const Coord &c)
    {
        x = c.x;
        y = c.y;
    }
    bool operator==(const Coord& other)
    {
        if(other.x == x&&other.y == y)
            return true;
        else
            return false;
    }
};
class ZuJi{
public:
    ZuJi()
    {
        top = -1;
    };
    void Push(Coord const x)
    {
        if(top+1 == 90)
        {
            cout<<"FULL.\n";
            exit(0);
        }
        element[++top] = Coord(x);
    }
    void Pop(Coord &x)
    {
        if(top == -1)
        {
            cout<<"Sorry, I'm missing (i-i).\n";
            exit(0);
        }
        x = Coord(element[top--]);

    }
    bool IsEmpty()
    {
        if(top == -1)
            return true;
        return false;
    }
    Coord GetTop()
    {
        return element[top];
    }
private:
    Coord element[90];
    int top;
};

class ZouMiGong{
public:
    ZouMiGong()
    {
        ifstream fin("input.txt",ios::in);
        fin>>maxx>>maxy;
        int i,j;
        for(i = 0; i < maxx; i++)
            for(j = 0; j < maxy; j++)
                fin>>MiGong[i][j];
        for(i = 0; i < maxx; i++)
            for(j = 0; j < maxy; j++)
                TrueMiGong[i][j] = MiGong[i][j];
        int x,y;
        fin>>x>>y;
        current = Coord(x,y);
        start = Coord(x,y);
        fin>>x>>y;
        ending = Coord(x,y);
        zuji.Push(current);
        fin.close();
    };
    bool S(Coord &current)
    {
        if(current.x >= 1 && MiGong[current.x-1][current.y] == 0)
        {
            MiGong[current.x-1][current.y] = 1;
            current.x--;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }

    }
    bool X(Coord &current)
    {
        if(current.x <= maxx - 2 && MiGong[current.x+1][current.y] == 0)
        {
            MiGong[current.x+1][current.y] = 1;
            current.x++;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Z(Coord &current)
    {
        if(current.y >= 1 && MiGong[current.x][current.y-1] == 0)
        {
            MiGong[current.x][current.y-1] = 1;
            current.y--;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Y(Coord &current)
    {
        if(current.y <= maxy - 2 && MiGong[current.x][current.y+1] == 0)
        {
            MiGong[current.x][current.y+1] = 1;
            current.y++;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool ZS(Coord &current)
    {
        if(current.y >= 1 && current.x >= 1 && MiGong[current.x-1][current.y-1] == 0)
        {
            MiGong[current.x-1][current.y-1] = 1;
            current.x--;
            current.y--;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool ZX(Coord &current)
    {

        if(current.y <= maxy - 2 && current.x >= 1 && MiGong[current.x-1][current.y+1] == 0)
        {
            MiGong[current.x-1][current.y+1] = 1;
            current.x--;
            current.y++;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool YS(Coord &current)
    {

        if(current.x <= maxx - 2 && current.y >= 1 && MiGong[current.x+1][current.y-1] == 0)
        {
            MiGong[current.x+1][current.y-1] = 1;
            current.x++;
            current.y--;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool YX(Coord &current)
    {
        if(current.x <= maxx - 2 && current.y <= maxx - 2 && MiGong[current.x+1][current.y+1] == 0)
        {
            MiGong[current.x+1][current.y+1] = 1;
            current.x++;
            current.y++;
            zuji.Push(current);
            return true;
        }
        else
        {
            return false;
        }
    }
    void ZouQi()
    {
        while(!(current == ending))
        {
            if(YX(current)){}
            else if (Y(current)){}
            else if (X(current)){}
            else if (S(current)){}
            else if (YS(current)){}
            else if (Z(current)){}
            else if (ZX(current)){}
            else if (ZS(current)){}
            else
            {
                zuji.Pop(current);
                MiGong[current.x][current.y] = 1;
            }
        }
    }
    void ZhanShi()
    {
        Coord way;
        int i, j;
        for(i = 0; i < maxx; i++)
        {
            for(j = 0; j < maxy; j++)
            {
                if(TrueMiGong[i][j] == 1)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                    cout<<"# ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                    cout<<TrueMiGong[i][j]<<" ";
            }
            cout<<endl;
        }
        while(!zuji.IsEmpty())
        {
            zuji.Pop(way);
            TrueMiGong[way.x][way.y] = 2;
        }
        cout<<"I'm ready...\n";
        cout<<"'#'-No,'0'-Yes,'*'-way\n";
        for(i = 0; i < maxx; i++)
        {
            for(j = 0; j < maxy; j++)
            {
                if(TrueMiGong[i][j] == 2)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
                    cout<<"* ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else if(TrueMiGong[i][j] == 1)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                    cout<<"# ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                    cout<<TrueMiGong[i][j]<<" ";
            }
            cout<<endl;
        }
    }
private:
    ZuJi zuji;
    Coord current, start, ending;
    int MiGong[9][9];
    int TrueMiGong[9][9];
    int maxx,maxy;
};

int main()
{
    ZouMiGong x;
    x.ZouQi();
    x.ZhanShi();
    return 0;
}

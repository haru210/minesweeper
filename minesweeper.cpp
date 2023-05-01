#include <iostream>
#include <random>
#include <ctime>
#include <conio.h>
#include <time.h>
using namespace std;


int map[12][12] = {0}; //0を数字ます、-1を爆弾マス、1を旗マスとする
int bomb[12][12] = {0};
int flags[12][12] = {0};
bool opened[12][12] = {false};
bool flag[12][12] = {false};

int selected_x = 1;
int selected_y = 1;
int bomb_number;

bool gameend = false;
bool firstclick = true;
bool gameover = false;
bool gameclear = false;

void write_map();
void place_bomb();
void place_number();
void open(int y, int x, bool code);
void build_flag(int y, int x);
bool sweepedcheck(int bomb);

int main()
{
    srand(time(NULL));
    cout << "操作説明\n";
    cout << "WASDで◎ の移動、スペースでマスオープンとコーディング、Fで旗立て、BackSpaceで強制終了\n";
    cout << "任意のキー入力でスタート\n";
    _getch();
    cout << "爆弾数を入力してね！(1~99)\n";
    cin >> bomb_number;
    if(bomb_number < 0 || bomb_number > 99)
    {
        cout << "正しい値を入力してね！\n";
        cin >> bomb_number;
        if(bomb_number < 0 || bomb_number > 99)
        {
            cout << "貴様は間違いを犯しすぎた。\n";
            _getch();
            return 0;
        }
    }
    write_map();
    while(!gameend)
    {
        switch(_getch())
        {
            case 'w':
            if(selected_y != 1) selected_y--;
            break;

            case 's':
            if(selected_y != 10) selected_y++;
            break;

            case 'a':
            if(selected_x != 1) selected_x--;
            break;

            case 'd':
            if(selected_x != 10) selected_x++;
            break;

            case ' ':
            if(!opened[selected_y][selected_x])
            {
                open(selected_y, selected_x, false);
            }
            else
            {
                open(selected_y, selected_x, true);
            }
            if(sweepedcheck(bomb_number))
            {
                gameend = true;
                gameclear = true;
            }
            break;

            case 'f':
            build_flag(selected_y, selected_x);
            break;

            case '\b':
            gameend = true;
            break;
        }
        write_map();
    }
    if(gameover)
    {
        cout << "Game Over!\n";
        _getch();
    }
    if(gameclear)
    {
        write_map();
        cout << "Game Clear!" << endl;
        _getch();
    }
}

void write_map()
{
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            if(selected_x == j && selected_y == i && gameclear == false)
            {
                cout << "◎" << ' ';
            }
            else if(flag[i][j])
            {
                cout << "□" << ' ';
            }
            else if(!opened[i][j])
            {
                cout << "■" << ' ';
            } 
            else
            {
                switch(map[i][j])
                {
                    case -1:
                    cout << 'X' << ' ';
                    break;
                    default:
                    if(bomb[i][j] == 0)
                    {
                        cout << "・";
                    }
                    else
                    {
                        cout << bomb[i][j] << ' ';
                    }
                    break;
                }
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

void place_bomb()
{
    int bomb_x, bomb_y;
    int i = 0;
    for(int i = 0;i < bomb_number; i++)
    {
        bomb_x = rand() % 10; //0~9
        bomb_y = rand() % 10; //0~9
        bomb_x++; //1~10
        bomb_y++; //1~10
        if(map[bomb_y][bomb_x] == -1 || opened[bomb_y][bomb_x] == true)
        {
            i--;
        }
        else
        {
            map[bomb_y][bomb_x] = -1;
            bomb[bomb_y-1][bomb_x-1]++;
            bomb[bomb_y-1][bomb_x]++;
            bomb[bomb_y-1][bomb_x+1]++;
            bomb[bomb_y][bomb_x-1]++;
            bomb[bomb_y][bomb_x+1]++;
            bomb[bomb_y+1][bomb_x-1]++;
            bomb[bomb_y+1][bomb_x]++;
            bomb[bomb_y+1][bomb_x+1]++;

        }
    }
    
}

bool sweepedcheck(int bomb)
{
    int cnt = 0;
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            if(opened[i][j])
            {
                cnt++;
            }
        }
    }
    if(cnt >= 100 - bomb)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
void open(int y, int x, bool code)
{
    if(y > 0 && y < 11 && x > 0 && x < 11)
    {
        if(code && flags[y][x] == bomb[y][x])
        {
            open(y+1, x+1, false);
            open(y+1, x, false);        
            open(y+1, x-1, false);        
            open(y, x+1, false);        
            open(y, x-1, false);        
            open(y-1, x-1, false);        
            open(y-1, x, false);      
            open(y-1, x+1, false);
        }
        if(opened[y][x]) return;
        if(flag[y][x]) return;
        if(map[y][x] != -1){
            opened[y][x] = true;
            if(firstclick)
            {
                place_bomb();
                firstclick = false;
            }
            if(bomb[y][x] == 0 && !code)
            {
                open(y+1, x+1, false);
                open(y+1, x, false);        
                open(y+1, x-1, false);        
                open(y, x+1, false);        
                open(y, x-1, false);        
                open(y-1, x-1, false);        
                open(y-1, x, false);      
                open(y-1, x+1, false);
            }
        }
        else
        {
            gameend = true;
            gameover = true;
        }
    }
}

void build_flag(int y, int x)
{
    if(!flag[y][x])
    {
        flag[y][x] = true;
        flags[y+1][x+1]++;
        flags[y+1][x]++;
        flags[y+1][x-1]++;
        flags[y][x+1]++;
        flags[y][x-1]++;
        flags[y-1][x-1]++;
        flags[y-1][x]++;
        flags[y-1][x+1]++;
    }
    else
    {
        flag[y][x] = false;
        flags[y+1][x+1]++;
        flags[y+1][x]++;
        flags[y+1][x-1]++;
        flags[y][x+1]++;
        flags[y][x-1]++;
        flags[y-1][x-1]++;
        flags[y-1][x]++;
        flags[y-1][x+1]++;
    }

}

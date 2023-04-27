#include <iostream>
#include <random>
#include <ctime>
#include <conio.h>
#include <time.h>
using namespace std;


int map[10][10] = {0}; //0~8を数字ます、-1を爆弾マスとする
int bomb[12][12] = {0};
bool opened[10][10] = {0};

int selected_x = 0;
int selected_y = 0;
int open_cnt = 0;
int bomb_number;

bool gameend = false;
bool firstclick = true;
bool gameover = false;
bool gameclear = false;

void write_map();
void place_bomb();
void place_number();

int main()
{
    srand(time(NULL));
    cout << "爆弾数を入力してね！(1~99)\n";
    cin >> bomb_number;
    if(bomb_number < 0 || bomb_number > 99)
    {
        cout << "は？やる気ある？もっかいちゃんとやって？\n";
        cin >> bomb_number;
        if(bomb_number < 0 || bomb_number > 99)
        {
            cout << "日本語読めるようになってから来いや\n";
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
            if(selected_y != 0) selected_y--;
            break;

            case 's':
            if(selected_y != 9) selected_y++;
            break;

            case 'a':
            if(selected_x != 0) selected_x--;
            break;

            case 'd':
            if(selected_x != 9) selected_x++;
            break;

            case ' ':
            if(map[selected_y][selected_x] != -1)
            {
                if(opened[selected_y][selected_x] == false)
                {
                    opened[selected_y][selected_x] = true;      
                    open_cnt++;
                }
                if(open_cnt >= 100 - bomb_number)
                {
                    gameend = true;
                    gameclear = true;
                }
            }
            else
            {
                gameend = true;
                gameover = true;
            } 
            if(firstclick) 
            {
                place_bomb();
                firstclick = false;
            }
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
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(selected_x == j && selected_y == i && gameclear == false)
            {
                cout << "◎" << ' ';
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
                    if(bomb[i+1][j+1] == 0)
                    {
                        cout << "・";
                    }
                    else
                    {
                        cout << bomb[i+1][j+1] << ' ';
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
        bomb_x = rand() % 10;
        bomb_y = rand() % 10;
        if(map[bomb_y][bomb_x] == -1 || opened[bomb_y][bomb_x] == true)
        {
            i--;
        }
        else
        {
            map[bomb_y][bomb_x] = -1;
            bomb_x++;
            bomb_y++;
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

    

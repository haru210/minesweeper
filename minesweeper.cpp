#include <iostream>
#include <conio.h>
using namespace std;

int map[10][10] = {0}; //0~8�𐔎��܂��Ƃ���
bool opened[10][10] = {false};

int selected_x = 0;
int selected_y = 0;

bool gameend = false;
void writemap();

int main()
{
    writemap();
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
            if(selected_y != 9) selected_x++;
            break;

            case '\b':
            gameend = true;
            break;
        }
        writemap();
    }
}

void writemap()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(selected_x == j && selected_y == i)
            {
                cout << "��" << ' ';
            }
            else if(!opened[i][j])
            {
                cout << "��" << ' ';
            }
            else
            {
                cout << map[i][j];
            }
        }
        cout << '\n';
    }
    cout << '\n';
}
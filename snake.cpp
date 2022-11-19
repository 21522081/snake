#include <bits/stdc++.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

const int width = 20;
const int height = 20;

struct Point
{
    int x;
    int y;
};

vector <Point> snake = {
    Point{ width / 2 + 2, height / 2},
    Point{ width / 2 + 1, height / 2},
    Point{ width / 2 , height / 2},
    Point{ width / 2 - 1, height / 2},
    Point{ width / 2 - 2, height / 2}
};

// void gotoxy(int x, int y)
// {
//   static HANDLE h = NULL;  
//   if(!h)
//     h = GetStdHandle(STD_OUTPUT_HANDLE);
//   COORD c = { x, y };  
//   SetConsoleCursorPosition(h,c);
// }
void gotoxy( int column, int line );
void DrawSnakeHead(Point p)
{
    gotoxy(p.x, p.y);
    cout << "X";
}

void DrawSnakePoint(Point p)
{
    gotoxy(p.x, p.y);
    cout << "0";
}

void DrawSnake()
{
    for (int i = 1; i < snake.size(); ++i)
        DrawSnakePoint(snake[i]);
    DrawSnakeHead(snake[0]);    
}

enum class Direction
{
    up,
    right,
    left,
    down
};
Direction direction = Direction::right;

void Move()
{
    for ( int i = snake.size() - 1; i > 0 ; --i)
        snake[i] = snake[i-1];
    if (direction == Direction::up)
        snake[0].y -= 1;
    else if (direction == Direction::down)
        snake[0].y += 1;
    else if (direction == Direction::right)
        snake[0].x += 1;
    else if (direction == Direction::left)
        snake[0].x -= 1;
}

int main()
{
    //DrawSnake();
    int speed = 100;
    while (1)
    {
        if (_kbhit())
        {
            char ch = _getch();
            ch = tolower(ch);
            if (ch == 'a')
                direction = Direction::left;
            else if ( ch == 'd')
                direction = Direction::right;
            else if ( ch == 's')
                direction = Direction::down;
            else if ( ch == 'w')
                direction = Direction::up;
            else if ( ch == 'q')
                break;
        }
        Move();
        DrawSnake();
        Sleep(speed);
        system("cls");

    }

    return 0;
}

void gotoxy( int column, int line )
    {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}
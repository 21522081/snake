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

void Boder()
{
    for (size_t i = 0; i < 60; i++)
    {
        cout << '-';
        gotoxy(0, 25);
    }
	for (size_t i = 0; i <= 60; i++)
        cout << '-';
	for (size_t i = 1; i < 25; i++)
	{
		gotoxy(0, i);
		cout << '|';
	}
	for (size_t i = 1; i < 25; i++)
	{
		gotoxy(60, i);
		cout << '|';
	}
}

bool WallHitted()
{
	return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == 60 || snake[0].y == 25;
}

bool BodyHitted()
{
	Point head = snake[0];
	for (size_t i = 1; i < snake.size(); i++)
		if (head.x == snake[i].x && head.y == snake[i].y)
			return true;
	return false;
}
// //Point apple;

// void genApple()
// {
// 	srand(time(0));
// 	int x = rand() % (WIDTH - 1) + 1;
// 	int y = rand() % (HEIGHT - 1) + 1;
// 	apple = {
// 		x,
// 		y,
// 	};
// 	// Sau khi có tọa độ quả táo thì vẽ lên màn hình
// 	gotoxy(x, y);
// 	cout << APPLE;
// }
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
        Boder();
        if (WallHitted())
            break;
        if (BodyHitted())
            break;
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

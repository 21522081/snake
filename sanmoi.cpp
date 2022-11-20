#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <time.h>
#include <time.h>
#include <time.h>
using namespace std;

#define width 40
#define height 20
#define body '*'
#define APPLE 'O'

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

 void gotoxy(int x, int y)
 {
   static HANDLE h = NULL;
   if(!h)
     h = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD c = { x, y };
   SetConsoleCursorPosition(h,c);
}
void gotoxy(int column, int line);
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
    for (int i = snake.size() - 1; i > 0; --i)
        snake[i] = snake[i - 1];
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
Point apple;
Point prevTail;

void genApple()
{
    srand(time(0));
    int x = rand() % (width - 1) + 1;
    int y = rand() % (height - 1) + 1;
    apple = {
        x,
        y,
    };
    // Sau khi có tọa độ quả táo thì vẽ lên màn hình
    gotoxy(x, y);
    cout << APPLE;
}
bool isAteApple()
{
    return snake[0].x == apple.x && snake[0].y == apple.y;
}
bool isBiteItself()
{
    Point head = snake[0];
    for (size_t i = 1; i < snake.size(); i++)
        if (head.x == snake[i].x && head.y == snake[i].y)
            return true;
    return false;
}
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void growing()
{
    snake.push_back(prevTail);
}
void displayScore()
{
    gotoxy(width + 5, 2);
    cout << "Your score: " << score;
}

int main()
{
    //DrawSnake();
    int speed = 100;
    void showEndMenu()
{
	system("cls");
	gotoxy(0, 0);
	cout << "End game!" << endl;
	cout << "Your score: " << score << endl;
	cout << "Do you want to play again ([y]/[n]): ";
	char option;
	cin >> option;
	option = tolower(option);
	if (option == 'y')
	{
		resetSnake();
		startGame();
	}
	else if (option == 'n')
		exit(1);
}
    
    while (1)
    {
        if (_kbhit())
        {
            char ch = _getch();
            ch = tolower(ch);
            if (ch == 'a')
                direction = Direction::left;
            else if (ch == 'd')
                direction = Direction::right;
            else if (ch == 's')
                direction = Direction::down;
            else if (ch == 'w')
                direction = Direction::up;
            else if (ch == 'q')
                break;
        }
        Move();
        DrawSnake();
        Boder();
        if (WallHitted())
            break;
        if (BodyHitted())
            break;
        system("cls");

    }
    ShowConsoleCursor(false);
    genApple();
    int score = 0;
    displayScore();
    if (isAteApple())
    {
        score++;
        displayScore();
        growing();
        genApple();
    }
    if (isBiteItself())
    {
        ShowConsoleCursor(true);
        showEndMenu();
        break;
    }
    if (isHitWall())
    {
        ShowConsoleCursor(true);
        showEndMenu();
        break;
    }

    return 0;
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

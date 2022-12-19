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
#define BODY '*'
#define APPLE 'O'

int speed = 100;
int score = 0;
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
Point apple;
Point prevTail;

/*
 void gotoxy(int x, int y)
 {
   static HANDLE h = NULL;
   if(!h)
     h = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD c = { x, y };
   SetConsoleCursorPosition(h,c);
}*/
void gotoxy(int column, int line);
void DrawSnakeHead(Point p);
void DrawSnakePoint(Point p);
void DrawSnake();
enum class Direction
{
    up,
    right,
    left,
    down
};
Direction direction = Direction::right;

void Move();
void Boder();
bool WallHitted();
bool BodyHitted();
void genApple();
bool isAteApple();
bool isBiteItself();
bool isHitWall();
void ShowConsoleCursor(bool showFlag);
void growing();
void displayScore();
void resetSnake();
void showStartMenu();
void showEndMenu();
void drawBox();
void move();
void drawHeadnTail();
void startGame();
void drawSnakePart(Point p);
void drawSnake();

int main()
{
    showStartMenu();
    return 0;
}
void resetSnake()
{
    score = 0;
    direction = Direction::right;
    snake = {
        Point{ width / 2 + 2, height / 2 },
        Point{ width / 2 + 1, height / 2 },
        Point{ width / 2, height / 2 },
        Point{ width / 2 - 1, height / 2 },
        Point{ width / 2 - 2, height / 2 }
    };
}
void showStartMenu()
{
    system("cls");
    cout << "Welcome to snake game!" << endl;
    cout << "Options:" << endl;
    cout << "1. Start" << endl;
    cout << "2. Quit" << endl;
    cout << "Your choice:(1 or 2) ";
    int option;
    cin >> option;
    if (option == 1)
    {
        system("cls");
        cout << "Chon level (1 - 5): ";
        int t;
        cin >> t;
        speed = 600 - t * 100; // Calculate speed depend on level
        system("cls");
        cout << "Tip: While playing game, you can press 'q' to quit";
        gotoxy(0, 3);
        cout << "Ready!";
        Sleep(1000);
        for (size_t i = 3; i > 0; i--)
        {
            gotoxy(0, 3);
            cout << i << "         ";
            Sleep(1000);
        }
        gotoxy(0, 3);
        cout << "GO!";
        Sleep(1000);
        startGame();
    }
    else if (option == 2)
        exit(1);
}
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
void drawBox()
   {
       for (size_t i = 0; i < width; i++)
           cout << '=';
       gotoxy(0, height);
       for (size_t i = 0; i < width; i++)
           cout << '=';
       for (size_t i = 1; i < height; i++)
       {
           gotoxy(0, i);
           cout << '|';
       }
       for (size_t i = 1; i < height; i++)
       {
           gotoxy(width, i);
           cout << '|';
       }
   }
void move()
   {
       prevTail = snake.back();
       for (size_t i = snake.size() - 1; i > 0; i--)
           snake[i] = snake[i - 1];
       if (direction == Direction::up)
           snake[0].y -= 1;
       else if (direction == Direction::down)
           snake[0].y += 1;
       else if (direction == Direction::left)
           snake[0].x -= 1;
       else if (direction == Direction::right)
           snake[0].x += 1;
   }
void drawHeadnTail()
   {
       gotoxy(snake[0].x, snake[0].y);
       cout << BODY;
       gotoxy(prevTail.x, prevTail.y);
       cout << ' '; // Clear the old tail
   }
   //main
void startGame()
   {
       system("cls");
       ShowConsoleCursor(false);

       drawBox();
       drawSnake();
       genApple();
       displayScore();

       while (true)
       {
           if (_kbhit())
           {
               char ch = _getch();
               ch = tolower(ch);
               if (ch == 'a' && direction != Direction::right)
                   direction = Direction::left;
               else if (ch == 'w' && direction != Direction::down)
                   direction = Direction::up;
               else if (ch == 's' && direction != Direction::up)
                   direction = Direction::down;
               else if (ch == 'd' && direction != Direction::left)
                   direction = Direction::right;
               else if (ch == 'q') // Quit game
               {
                   showEndMenu();
                   break;
               }
           }
           move();
           drawHeadnTail();
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
           Sleep(speed);
       }
   }
void drawSnakePart(Point p)
   {
       gotoxy(p.x, p.y);
       cout << BODY;
   }
void drawSnake()
   {
       for (size_t i = 0; i < snake.size(); i++)
           drawSnakePart(snake[i]);
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
void genApple()
{
    srand(time(0));
    int x = rand() % (width - 1) + 1;
    int y = rand() % (height - 1) + 1;
    apple = {
        x,
        y,
    };

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
bool isHitWall()
{
    return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == width || snake[0].y == height;
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


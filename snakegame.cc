#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 20, height = 20;
int x, y, FruitX, FruitY, score;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

void Setup()
{

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    FruitX = (rand() % width) + 1;
    FruitY = (rand() % height) + 1;
    score = 0;
}

void Draw()
{

    clear();

    for (int i = 0; i < width + 2; i++)
        mvprintw(0, i, "+");

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 | i == 21)
                mvprintw(i, j, "+");
            else if (j == 0 | j == 21)
                mvprintw(i, j, "+");
            else if (i == y && j == x)
                mvprintw(i, j, "O");
            else if (i == FruitY && j == FruitX)
                mvprintw(i, j, "@");
        }
    }

    mvprintw(23, 0, "Score %d", score);

    refresh();
}

void Input()
{

    // what key changes mean for snake head
    keypad(stdscr, TRUE);
    halfdelay(1);

    int c = getch();

    switch (c)
    {
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    // q key
    case 113:
        gameOver = true;
        break;
    }
}

void Logic()
{
    // move snake head from key changes
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // gameover if you hit the game border
    if (x > width || x < 1 || y < 1 || y > height)
        gameOver = true;

    // when snake eats fruit
    if (x == FruitX && y == FruitY)
    {
        score++;
        FruitX = (rand() % width) + 1;
        FruitY = (rand() % height) + 1;
    }
}

int main()
{

    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }

    getch();
    endwin();

    return 0;
}
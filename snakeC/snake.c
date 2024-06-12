#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/* Define constants for height and width of the rectangle */
#define HEIGHT 20
#define WIDTH 60

/* Stuff I need */
enum Direction { Up = 1, Down = 2, Right = 3, Left = 4 };
typedef struct { int snakex, snakey, tail, tailx[50], taily[50], snakelength; enum Direction path;} Snake;
typedef struct { int fruitx; int fruity; } Fruit;
typedef struct { int score; int gameover; } Player;
typedef struct { int height; int width; } Map;

Snake Naja; Fruit Apple; Player User; Map Square;

/* Snake fragments moving */
void shifter(int arr[], int size)
{
    for (int i = size - 2; i >= 0; i--)
    {
        arr[i + 1] = arr[i];
    }
}

void position()
{
    User.gameover = 0;
    Square.height = HEIGHT;
    Square.width = WIDTH;
    Naja.snakelength = 0;
    Naja.snakex = Square.height/2;
    Naja.snakey = Square.width/2;
    Naja.tail = 0;
    Naja.path = Right;
    Apple.fruitx = 1 + rand() % (Square.height-2);
    Apple.fruity = 1 + rand() % (Square.width-2);
}

/* Function to draw a rectangle with specified height and width */
void boundary(int h, int w)
{
    int i, j;
    for (i = 0; i <= h; i++) /* Rows */
    {
        for (j = 0; j <= w; j++) /* Columns */
        {
            if (i == 0 || i == h || j == 0 || j == w)
            {
                printw("#");
            }
            else if (i == Naja.snakex && j == Naja.snakey)
            {
                printw("0");
            }
             else if (i == Apple.fruitx && j == Apple.fruity)
            {
                printw("F");
            }
            else
            {
                int istail = 0;
                for (int z = 0; z < Naja.snakelength; z++)
                {
                    if (i == Naja.tailx[z] && j == Naja.taily[z])
                    {
                        printw("o");
                        istail = 1;
                        break;
                    }
                }
                if (!istail)
                {
                    printw(" ");
                }
            }
        }
        printw("\n");
    }

    if (Naja.snakex == 0 || Naja.snakex == h-1 || Naja.snakey == 0 || Naja.snakey == w-1)
    {
        if (User.score != 0)
        {
            User.score = User.score - 10;
            Naja.snakex = Square.height/2;
            Naja.snakey = Square.width/2;
            Naja.snakelength--;
        } 
        else
        User.gameover = 1;
    }

    for (int z = 0; z < Naja.snakelength; z++)
    {
        if (Naja.snakex == Naja.tailx[z] && Naja.snakey == Naja.taily[z])
        {
            if (User.score != 0)
            {
                User.score = User.score - 10;
                Naja.snakex = Square.height/2;
                Naja.snakey = Square.width/2;
                Naja.snakelength--;
            } 
            else
            User.gameover = 1;
        }
    }
}

void keyboard()
{
    switch(getch())
    {
        case KEY_UP:
            Naja.path = Up;
            break;
        case KEY_DOWN:
            Naja.path = Down;
            break;
        case KEY_RIGHT:
            Naja.path = Right;
            break;
        case KEY_LEFT:
            Naja.path = Left;
            break;
        case 'x':
            exit(0);
    }    
}

/*In general, you shouldn't mix stdio (printf()) with curses. 
 ,If you change the printf calls to printw(), 
 the square will be rendered. 
 (I'd also suggest replacing the usleep() delay, 
 if it were uncommented, 
 with an equivalent call to curses' own napms() function 
 (just divide the parameter by 1000).)*/

void game()
{
    shifter(Naja.tailx, 50);
    shifter(Naja.taily, 50);

    /* updates the position of the first element of the tail */
    Naja.tailx[0] = Naja.snakex;
    Naja.taily[0] = Naja.snakey;

    halfdelay(3);
    switch(Naja.path)
    {
        case Up:
            Naja.snakex--;
            break;
        case Down:
            Naja.snakex++;
            break;
        case Right:
            Naja.snakey++;
            break;
        case Left:
            Naja.snakey--;
            break;
    }

    if (Apple.fruitx == Naja.snakex && Apple.fruity == Naja.snakey)
    {
        User.score += 10;
        Apple.fruitx = 1 + rand() % (Square.height - 2);
        Apple.fruity = 1 + rand() % (Square.width - 2);
        Naja.snakelength++;
        Naja.tail++;
    }
}

int main() {
    /* Curses initialization shit */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(FALSE);

    User.score = 0;
    position();
    
    // Game loop
    while (!User.gameover)
    {
        /* Clear the screen */
        clear();

        /* Shape drawing */
        boundary(Square.height, Square.width);

        /* Debugging stuff */
        printw("Fruit position: %d %d\n", Apple.fruitx, Apple.fruity);
        printw("Snake position: %d %d\n", Naja.snakex, Naja.snakey);
        printw("Score: %d\n", User.score);
        
        /* Input and Logic of Snake Game */
        keyboard();
        game();

        /* Refresh the screen */
        refresh();

        /* Slow down le snek */
        napms(80);
    }

    /* Curses cleaning or whatever */
    endwin();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <string.h>

/* Height and width of the rectangle */
#define HEIGHT 25
#define WIDTH 25

/* Stuff I need */
enum Direction { Up = 1, Down = 2, Right = 3, Left = 4};
typedef struct { int x, y; enum Direction path; } Car;
typedef struct { int x, y; enum Direction smash; } Enemy;
typedef struct { int score; int gameover; } Player;
typedef struct { int height; int width; } Road;

Car Autobot; Enemy Decepticon; Enemy Megatron; Player User; Road Trackmania;

/* Arrays */
char yCoordinates[4] = {8, 16, 24};

void position() {
    User.gameover = 0;
    Trackmania.height = HEIGHT;
    Trackmania.width = WIDTH;
    Autobot.x = HEIGHT - 6;
    Autobot.y = 9;
    Decepticon.x = HEIGHT - 23;
    /* 24, 16, 8 */
    Decepticon.y = WIDTH - yCoordinates[rand() % 3];
}

void boundary(int h, int w) {
    int i, j;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if (i <= 1 ||  i >= HEIGHT-2) {
                printw("_");
            }
            else if (j == 0 || j == WIDTH-1 || j == WIDTH/3 || j == 2*WIDTH/3) {
                printw("|");
            }
            else if (i >= Autobot.x && i < Autobot.x + 4 && j >= Autobot.y && j < Autobot.y + 4) {
                    if (i == Autobot.x && j == Autobot.y)
                    {
                        printw("0|   |0");
                        j+=6;
                    }
                    if (i == Autobot.x + 1 && j == Autobot.y)
                    {
                        printw(" || ||");
                        j+=5;
                    }
                    if (i == Autobot.x + 2 && j == Autobot.y)
                    {
                        printw(" || ||");
                        j+=5;
                    }
                    if (i == Autobot.x + 3 && j == Autobot.y)
                    {
                        printw("0|   |0");
                        j+=6;
                    }
                }
            else if (i >= Decepticon.x && i < Decepticon.x + 4 && j >= Decepticon.y && j < Decepticon.y + 4) {
                    if (i == Decepticon.x && j == Decepticon.y + 3) {
                        printw("0|   |0");
                        j+=3;
                    }
                    else if (i == Decepticon.x + 1 && j == Decepticon.y + 2) {
                        printw(" || ||");
                        j+=3;
                    }
                    else if (i == Decepticon.x + 2 && j == Decepticon.y + 1) {
                        printw(" || ||");
                        j+=4;
                    }
                    else if (i == Decepticon.x + 3 && j == Decepticon.y) {
                        printw("0|   |0");
                        j+=6;
                    }
            }
            else if (i >= Megatron.x && i < Megatron.x + 4 && j >= Megatron.y && j < Megatron.y + 4 && Megatron.x != 0 && Megatron.y != 0) {
                    if (i == Megatron.x && j == Megatron.y + 3) {
                        printw("0|   |0");
                        j+=3;
                    }
                    else if (i == Megatron.x + 1 && j == Megatron.y + 2) {
                        printw(" || ||");
                        j+=3;
                    }
                    else if (i == Megatron.x + 2 && j == Megatron.y + 1) {
                        printw(" || ||");
                        j+=4;
                    }
                    else if (i == Megatron.x + 3 && j == Megatron.y) {
                        printw("0|   |0");
                        j+=6;
                    }
            }
            else {
                printw(" ");
            }
        }
        printw("\n");
    }
}

void keyboard()
{
    Autobot.path = Up;
    switch(getch())
    {
        case KEY_RIGHT:
            Autobot.path = 3;
            break;
        case KEY_LEFT:
            Autobot.path = 4;
            break;
        case KEY_UP:
            Autobot.path = 1;
            break;
        case KEY_DOWN:
            Autobot.path = 2;
            break;
        case 'x':
            exit(0);
        Default:
            Autobot.path = 0;
    }
}

void twoCars() {
    if (Megatron.x == Trackmania.height - 1) {
        Megatron.x = 1;
        Megatron.y = WIDTH - yCoordinates[rand() % 3];
        User.score += 20;
    } else {
        halfdelay(1);
        Megatron.x++;
    }
    if (Decepticon.x == 15 && Megatron.x == 0) {
        Megatron.x = 1;
        Megatron.y = WIDTH - yCoordinates[rand() % 3];
    }
    if ((Autobot.x + 4 >= Megatron.x && Autobot.x <= Megatron.x + 4) &&
        (Autobot.y + 4 >= Megatron.y && Autobot.y <= Megatron.y + 4)) {
        Autobot.x = HEIGHT - 6;
        Autobot.y = 9;
        if (User.score != 0) {
            Megatron.x = 1;
            Megatron.y = WIDTH - yCoordinates[rand() % 3];
            User.score -= 20;
        } else {
            User.gameover = 1;
        }
    }
}

void game()
{
    if (User.score >= 30) {
        if (Megatron.x == Trackmania.height - 1) {
            Megatron.x = 1;
            Megatron.y = WIDTH - yCoordinates[rand() % 3];
            User.score += 20;
        } else {
            halfdelay(1);
            Megatron.x++;
        }
        if (Decepticon.x == 5) {
            Megatron.x = 1;
            Megatron.y = WIDTH - yCoordinates[rand() % 3];
        }
        if ((Autobot.x + 4 >= Megatron.x && Autobot.x <= Megatron.x + 4) &&
            (Autobot.y + 4 >= Megatron.y && Autobot.y <= Megatron.y + 4)) {
            Autobot.x = HEIGHT - 6;
            Autobot.y = 9;
            if (User.score != 0) {
                Megatron.x = 1;
                Megatron.y = WIDTH - yCoordinates[rand() % 3];
                User.score -= 20;
            } else {
                User.gameover = 1;
            }
        }
    }

    if (Autobot.x > 0 && Autobot.x < Trackmania.height-1 && Autobot.y > 0 && Autobot.y < Trackmania.width-1)
    {
        switch(Autobot.path)
        {
            case Right:
                Autobot.y = Autobot.y + Trackmania.width/3;
                break;
            case Left:
                Autobot.y = Autobot.y - Trackmania.width/3;
                break;
            case Up:
                Autobot.x = Autobot.x - 1;
                break;
            case Down:
                Autobot.x = Autobot.x + 1;
                break;
        }
    }
    else
    {
        User.gameover = 1;
    }
    if (Decepticon.x == Trackmania.height - 1) {
        Decepticon.x = 1;
        Decepticon.y = WIDTH - yCoordinates[rand() % 3];
        User.score += 10;
    } else {
        halfdelay(3);
        Decepticon.x++;
    }
    if ((Autobot.x + 4 >= Decepticon.x && Autobot.x <= Decepticon.x + 4) &&
        (Autobot.y + 4 >= Decepticon.y && Autobot.y <= Decepticon.y + 4)) {
        Autobot.x = HEIGHT - 6;
        Autobot.y = 9;
        if (User.score != 0) {
            Decepticon.x = 1;
            Decepticon.y = WIDTH - yCoordinates[rand() % 3];
            User.score -= 10;
        }
        else
            User.gameover = 1;
    }
}

int main() {
    /* Curses initialization shit */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(FALSE);

    /* Print a message to start the game */
    printw("Press any key to start the game...");
    refresh();
    getch();

    /* Clear the screen and start the game loop */
    clear();
    position();

    /* Game loop */
    while (!User.gameover)
    {
        /* Clear the screen */
        clear();

        /* Shape drawing */
        boundary(Trackmania.height, Trackmania.width);

        /* Debugging stuff */
        printw("\n");
        printw("Your score: %d\n", User.score);
        
        /* Input and Logic */
        keyboard();
        game();
        
        /* Refresh the screen */
        refresh();

        /* idk if i will use it */
        /* napms(80); */
    }

    /* Curses cleaning or whatever */
        endwin();
        
        printf("/\n");
        printf("  ________                       \n");
        printf(" /  _____/_____    _____   ____  \n");
        printf("/   \\  ___\\__  \\  /     \\_/ __ \\ \n");
        printf("\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/ \n");
        printf(" \\______  (____  /__|_|  /\\___  >\n");
        printf("        \\/     \\/      \\/     \\/ \n");
        printf("  _______  __ ___________ \n");
        printf(" /  _ \\  \\/ // __ \\_  __ \\\n");
        printf("(  <_> )   /\\  ___/|  | \\/\n");
        printf(" \\____/ \\_/  \\___  >__|   \n");
        printf("                 \\/        \n");
    

    return 0;
}

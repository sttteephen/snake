#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h> 
#include <ncurses.h>
#include <time.h>
#include "msleep.h"

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 15

void print_border();
void print_intro();
void print_endgame(int score);
void print_board(int headx, int heady, int foodx, int foody, int score);

int main()
{
    // initialize ncurses window and settings 
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    srand(time(0));

    int play;
    print_intro();

    if((play = getch()) == '1')
    {
        nodelay(stdscr, TRUE);  // do not pause execution for input

        int headx, heady;    // coordinates of the snake head
        int foodx, foody;    // coordinates of the food
        int score, input, direction;
        headx = heady = score = 0;
        foodx = rand() % BOARD_WIDTH;
        foody = rand() % BOARD_HEIGHT;

        // game loop
        int run = 1;
        while(run)
        {   
            clear();

            // check for user input and use it to change direction of player
            switch (input = getch())
            {
                case KEY_LEFT:
                    direction = 1;
                    break;
                case KEY_RIGHT:
                    direction = 2;
                    break;
                case KEY_UP:
                    direction = 3;
                    break;
                case KEY_DOWN:
                    direction = 4;
                    break;
                case '0':
                    run = 0;
                    break;
                default:
                    break;
            }

            // move player in direction as long as they have not reached the edge
            if(direction == 1) 
            {
                headx--;
                if(headx == -1){
                    headx++;
                    break;
                }
            }
            else if(direction == 2) 
            {
                headx++;
                if(headx == BOARD_WIDTH)
                {
                    headx--;
                    break;
                }
            }
            else if(direction == 3) 
            {
                heady--;
                if(heady == -1)
                {
                    heady++;
                    break;
                }
            }
            else if(direction == 4) 
            {
                heady++;
                if(heady == BOARD_HEIGHT)
                {
                    heady--;
                    break;
                }
            }

            // if player has come in contact with food increase the score and move the food
            if(headx == foodx && heady == foody){
                foodx = rand() % BOARD_WIDTH;
                foody = rand() % BOARD_HEIGHT;
                score += 10;
            }

            // print the board
            print_board(headx, heady, foodx, foody, score);
            // pause execution
            msleep(80);
        }
        print_endgame(score);
    }

    endwin();
    return 0;
}


// print the frame using the coordinates of objects to print
void print_board(int headx, int heady, int foodx, int foody, int score)
{
    // print the top border
    print_border();
    for(int y = 0; y < BOARD_HEIGHT; y++)
    {
        printw("|");
        for(int x = 0; x < BOARD_WIDTH; x++)
        {   
            if(y == heady && x == headx) {printw("0");}
            else if(y == foody && x == foodx)  {printw("X");}
            else {printw(" ");}
        }
        printw("|\n");
    }
    print_border();

    printw("Score: %d\t", score);

    // update the screen
    refresh();
}


// prints top and bottom border of the board
void print_border()
{
    printw("+");
    for(int i = 0; i < BOARD_WIDTH; i++) {printw("-");}
    printw("+\n");
}


// print animated intro screen 
void print_intro()
{
    int snake_len = 15;
    int point_pos = 17;
    int space_before = -snake_len;
    int line_len = 21;

    int run = 1;
    while(run)
    {
        // pause for 60 milliseconds then clear screen after every frame
        msleep(60);
        clear();

        printw("\n");
        printw("    Welcome to Snake\n");

        // print the last line based on the movement of the snake
        for(int i = 0; i < line_len; i++)
        {
            if(i < space_before)
            {
                printw(" ");
            }
            else if(i < space_before + snake_len)
            {
                printw("=");
            }
            else if(i == point_pos)
            {
                printw("X");
            }
            else
            {
                printw(" ");
            }
        }
        printw("\n");

        space_before++; // increase the number of spaces before the snake each frame
        if(space_before + snake_len == point_pos) {snake_len++;}
        if(space_before + snake_len == line_len) {run = 0;}
        refresh();
    }

    printw("   - Press 1 to Play\n");
    printw("   - Press 0 to Exit\n");
    refresh();
}


// print GAME OVER
void print_endgame(int score)
{
    clear();
    printw("GAME OVER\n");
    printw("Score: %d\n", score);
    char exit;
    while((exit = getch()) != '0');
    refresh();
}
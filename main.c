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
int msleep(long msec);


int main()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    srand(time(0));

    int play;
    print_intro();

    if((play = getch()) == '1')
    {
        nodelay(stdscr, TRUE);


        int headx, heady, foodx, foody, score, input, direction, run;
        headx = heady = score = 0;
        foodx = rand() % BOARD_WIDTH;
        foody = rand() % BOARD_HEIGHT;

        refresh();
        getch();
        int count = 0;

        // game loop
        run = 1;
        while(run)
        {   
            clear();

            // check for user input and use it to change direction of player
            input = getch();
            if(input == KEY_LEFT) {direction = 1;}
            else if(input == KEY_RIGHT) {direction = 2;}
            else if(input == KEY_UP) {direction = 3;}
            else if(input == KEY_DOWN) {direction = 4;}
            else if(input == '0') {break;}

            if(direction == 1 && headx > 0) {headx--;}
            else if(direction == 2 && headx < BOARD_WIDTH-1) {headx++;}
            else if(direction == 3 && heady > 0) {heady--;}
            else if(direction == 4 && heady < BOARD_HEIGHT-1) {heady++;}

            if(headx == foodx && heady == foody){
                foodx = rand() % BOARD_WIDTH;
                foody = rand() % BOARD_HEIGHT;
                score += 10;
            }

            // print the board
            print_border();
            for(int i = 0; i < BOARD_HEIGHT; i++)
            {
                printw("|");
                for(int j = 0; j < BOARD_WIDTH; j++)
                {   
                    if(i == heady && j == headx) {printw("0");}
                    else if(i == foody && j == foodx)  {printw("X");}
                    else {printw(" ");}
                }
                printw("|\n");
            }
            print_border();

            printw("Score: %d\t", score);
            printw("%d\n", count++);

            // update the screen and pause exectution
            refresh();
            msleep(80);
        }
    }
    
    endwin();
    return 0;
}

// prints top and bottom border of the board
void print_border()
{
    printw("+");
    for(int k = 0; k < BOARD_WIDTH; k++) {printw("-");}
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
        // pause for 70 milliseconds then clear screen after every frame
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
        //+ snake_len + 1
        refresh();
    }

    printw("   - Press 1 to Play\n");
    printw("   - Press 0 to Exit\n");
    refresh();
}
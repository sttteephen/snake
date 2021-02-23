#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>    


#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #define CLEAR system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR system("cls");
#endif


void print_intro();
int msleep(long);


int main()
{
    char input[10];
    print_intro();
    fgets(input, 10, stdin);

    return 0;
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
        CLEAR;

        printf("\n");
        printf("    Welcome to Snake\n");

        // print the last line based on the movement of the snake
        for(int i = 0; i < line_len; i++)
        {
            if(i < space_before)
            {
                printf(" ");
            }
            else if(i < space_before + snake_len)
            {
                printf("=");
            }
            else if(i == point_pos)
            {
                printf("0");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");

        space_before++; // increase the number of spaces before the snake each frame
        if(space_before + snake_len == point_pos) {snake_len++;}
        if(space_before + snake_len == line_len) {run = 0;}
        //+ snake_len + 1
    }

    printf("   - Press 1 to Play\n");
    printf("   - Press 0 to Exit\n");
}


// pauses execution for the given amount of milliseconds
// credit: https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
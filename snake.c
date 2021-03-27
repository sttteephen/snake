#include "snake.h"
#include <stdlib.h>

// initialize a new snake with a head in the middle of the board
void init_snake(struct Snake *snake, int width, int height, int max)
{
    // allocate memory for an array of snake segments
    snake->segment_list = (struct Segment*)malloc(sizeof(struct Segment)*max);

    // add head segment positioned in the middle of the board
    struct Segment head;
    head.posx = width/2;
    head.posy = height/2;
    snake->segment_list[0] = head;

    // set the snakes segment counter and max size
    snake->size = 1;
    snake->max = max;
}

// move the snake one space in the given direction
void move_snake(struct Snake *snake, int direction)
{
    int prevx = snake->segment_list[0].posx;
    int prevy = snake->segment_list[0].posy;

    // move the head segment in the given direction
    if(direction == 1) 
    {
        snake->segment_list[0].posx--;
    }
    else if(direction == 2) 
    {
        snake->segment_list[0].posx++;
    }
    else if(direction == 3) 
    {
        snake->segment_list[0].posy--;
    }
    else if(direction == 4) 
    {
        snake->segment_list[0].posy++;
    }

    int i = 1;
    while(i < snake->size)
    {
        // loop through the other segments moving them into the previous ones position
        int tempx = snake->segment_list[i].posx;
        int tempy = snake->segment_list[i].posy;
        snake->segment_list[i].posx = prevx;
        snake->segment_list[i].posy = prevy;
        prevx = tempx;
        prevy = tempy;
        i++;
    }
}

// add a segment to the snake 
void add_segment(struct Snake *snake)
{
    if(snake->size == snake->max)
        double_array(snake);

    // initialize body segment and append it to snake
    struct Segment body;
    // new segments position is off screen, it will be added in the next frame when the snake moves
    body.posx = -1;
    body.posy = -1;
    snake->segment_list[snake->size] = body;

    snake->size++;
}

// double the space allocated to the snakes segment array
void double_array(struct Snake *snake)
{
    // allocate new memory
    snake->max *= 2;
    struct Segment *new_array = (struct Segment*)malloc(sizeof(struct Segment) * snake->max);

    // copy over contents
    int i;
    for(i=0; i<snake->max/2; i++)
    {
        new_array[i] = snake->segment_list[i];
    }

    free(snake->segment_list);
    snake->segment_list = new_array;
}

// check the head of the snake is not colliding with the body or a wall
// return 0 if it is, 1 if it is not
int check_collision(struct Snake *snake, int width, int height)
{
    int headx = snake->segment_list[0].posx;
    int heady = snake->segment_list[0].posy;
    int no_collision = 1;

    if(headx == -1 || headx == width || heady == -1 || heady == height)
    {
        no_collision = 0;
        return no_collision;
    }

    int i = 1;
    while(i < snake->size)
    {
        // loop through the body segments checking if the have collided
        if(snake->segment_list[i].posx == headx && snake->segment_list[i].posy == heady) 
        {
            no_collision = 0;
            return no_collision;
        }

        i++;
    }
    return no_collision;
}

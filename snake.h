#pragma once

// represents a segment of the snake by its position on the board
struct Segment
{
    int posx;
    int posy;
};

// represents the snake by a list of segments
struct Snake
{
    struct Segment *segment_list;
    int max;
    int size;
};

// initialize a new snake with a head in the middle of the board
void init_snake(struct Snake *snake, int width, int height, int max);

// move the snake one space in the given direction
void move_snake(struct Snake *, int direction);

// add a segment to the snake
void add_segment(struct Snake *);

// double the size of the segments array
void double_array(struct Snake *snake);

// check the head of the snake is not colliding with the body or a wall, return 0 if it is, 1 if it is not
int check_collision(struct Snake *, int width, int height);
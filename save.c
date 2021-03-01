void init_snake(struct Segment s[50])
{
    struct Segment head;
    head.posx = BOARD_WIDTH/2;
    head.posy = BOARD_HEIGHT/2;
    s[0] = head;

    struct Segment end;
    end.posx = -1;
    end.posy = -1;
    s[1] = end;
}

int move_snake(int direction, struct Segment snake[50])
{
    int nocollide = 1;
    int prevx = snake[0].posx;
    int prevy = snake[0].posy;
    // move player in direction then check if they have reached an edge
    if(direction == 1) 
    {
        snake[0].posx--;
        if(snake[0].posx == -1){
            snake[0].posx++;
            nocollide = 0;
        }
    }
    else if(direction == 2) 
    {
        snake[0].posx++;
        if(snake[0].posx == BOARD_WIDTH)
        {
            snake[0].posx--;
            nocollide = 0;
        }
    }
    else if(direction == 3) 
    {
        snake[0].posy--;
        if(snake[0].posy == -1)
        {
            snake[0].posy++;
            nocollide = 0;
        }
    }
    else if(direction == 4) 
    {
        snake[0].posy++;
        if(snake[0].posy == BOARD_HEIGHT)
        {
            snake[0].posy--;
            nocollide = 0;
        }
    }

    int i = 1;
    while(snake[i].posx != -1)
    {
        int tempx = snake[i].posx;
        int tempy = snake[i].posy;
        snake[i].posx = prevx;
        snake[i].posy = prevy;
        prevx = tempx;
        prevy = tempy;
        i++;
    }
    
    return nocollide;
}

void add_segment(struct Segment snake[50])
{
    struct Segment body;
    body.posx = 0;
    body.posy = 0;
    snake[1] = body;

    struct Segment end;
    body.posx = -1;
    body.posy = -1;
    snake[2] = body;
}
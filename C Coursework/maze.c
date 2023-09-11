#include <stdio.h>
#include "graphics.h"

void initialize_maze(int path_grid[])
{
    setWindowSize(560, 560);
    background();

    int current_square, row, column, rect_x, rect_y;
    rect_x = rect_y = 40;
    current_square = row = column = 0;

    for(row = 0; row < 12; row ++)
    {
        rect_x = 40;

        for(column = 0; column < 12; column ++)
        {
            if (path_grid[current_square] == 1)
            {
                drawRect(rect_x,rect_y,40,40);
            }
            else if (path_grid[current_square] == 0)
            {
                fillRect(rect_x,rect_y,40,40);
            }
            else
            {
                setColour(lightgray);
                fillRect(rect_x,rect_y,40,40);
                setColour(black);
            }
            current_square ++;
            rect_x += 40;
        }

        rect_y += 40;
    }
}

struct robot
{
    int back_left_x;
    int back_left_y;
    int back_right_x;
    int back_right_y;
    int front_x;
    int front_y;
    char direction;
};

void draw_robot(struct robot robot_info)
{
    clear();
    int x_coordinates[] = {robot_info.back_left_x,robot_info.back_right_x,robot_info.front_x};
    int y_coordinates[] = {robot_info.back_left_y,robot_info.back_right_y,robot_info.front_y};
    fillPolygon(3,x_coordinates,y_coordinates);
}

struct robot left(struct robot robot_info)
{
    switch (robot_info.direction)
    {
    case 'n':
        robot_info.back_left_x += 40;
        robot_info.back_right_y -= 40;
        robot_info.front_x -= 20;
        robot_info.front_y += 20;
        robot_info.direction = 'w';
        break;
    case 'e':
        robot_info.back_left_y += 40;
        robot_info.back_right_x += 40;
        robot_info.front_x -= 20;
        robot_info.front_y -= 20;
        robot_info.direction = 'n';
        break;
    case 's':
        robot_info.back_left_x -= 40;
        robot_info.back_right_y += 40;
        robot_info.front_x += 20;
        robot_info.front_y -= 20;
        robot_info.direction = 'e';
        break;
    case 'w':
        robot_info.back_left_y -= 40;
        robot_info.back_right_x -= 40;
        robot_info.front_x += 20;
        robot_info.front_y += 20;
        robot_info.direction = 's';
        break;
    }
    draw_robot(robot_info);
    return robot_info;
}

struct robot right(struct robot robot_info)
{
    switch (robot_info.direction)
    {
    case 'n':
        robot_info.back_left_y -= 40;
        robot_info.back_right_x -= 40;
        robot_info.front_x += 20;
        robot_info.front_y += 20;
        robot_info.direction = 'e';
        break;
    case 'e':
        robot_info.back_left_x += 40;
        robot_info.back_right_y -= 40;
        robot_info.front_x -= 20;
        robot_info.front_y += 20;
        robot_info.direction = 's';
        break;
    case 's':
        robot_info.back_left_y += 40;
        robot_info.back_right_x += 40;
        robot_info.front_x -= 20;
        robot_info.front_y -= 20;
        robot_info.direction = 'w';
        break;
    case 'w':
        robot_info.back_left_x -= 40;
        robot_info.back_right_y += 40;
        robot_info.front_x += 20;
        robot_info.front_y -= 20;
        robot_info.direction = 'n';
        break;
    }
    draw_robot(robot_info);
    return robot_info;
}

int can_move(int path_grid[],struct robot robot_info)
{
    int number_rows, number_columns;
    switch (robot_info.direction)
    {
    case 'n':
        number_rows = robot_info.front_y / 40 - 2;
        number_columns = (robot_info.front_x + 20) / 40 - 2;
        break;
    case 'e':
        number_rows = (robot_info.front_y + 20) /40 - 2;
        number_columns = robot_info.front_x / 40 - 1;
        break;
    case 's':
        number_rows = robot_info.front_y / 40 - 1;
        number_columns = (robot_info.front_x + 20) / 40 - 2;
        break;
    case 'w':
        number_rows = (robot_info.front_y + 20) /40 - 2;
        number_columns = robot_info.front_x / 40 - 2;
        break;
    }
    /* calculates array position of square robot points to */
    
    if(path_grid[12 * number_rows + number_columns] == 1)
    {
        return 1;
    }
    else if(path_grid[12 * number_rows + number_columns] == 2)
    {
        return 2;
    }
    return 0;
}

struct robot forward(int path_grid[],struct robot robot_info)
{
    if(can_move(path_grid,robot_info))
    {
        switch (robot_info.direction)
        {
        case 'n':
            robot_info.back_left_y -= 40;
            robot_info.back_right_y -= 40;
            robot_info.front_y -= 40;
            break;
        case 'e':
            robot_info.back_left_x += 40;
            robot_info.back_right_x += 40;
            robot_info.front_x += 40;
            break;
        case 's':
            robot_info.back_left_y += 40;
            robot_info.back_right_y += 40;
            robot_info.front_y += 40;
            break;
        case 'w':
            robot_info.back_left_x -= 40;
            robot_info.back_right_x -= 40;
            robot_info.front_x -= 40;
            break;
        }
        draw_robot(robot_info);
        sleep(500);
    }
    return robot_info;
}

int at_marker(int path_grid[],struct robot robot_info)
{
    if (can_move(path_grid,robot_info) == 2)
    {
        forward(path_grid,robot_info);
        return 1;
    }
    return 0;
}

struct robot traverse_maze(int path_grid[],struct robot robot_info)
{
    if (at_marker(path_grid,robot_info) == 1)
    {
        return robot_info;
    }

    if(can_move(path_grid,robot_info) == 0)
    {
        robot_info = right(robot_info);

        if(can_move(path_grid,robot_info) == 0)
        {
            robot_info = left(robot_info);
            robot_info = left(robot_info);
        }
    }

    robot_info = forward(path_grid,robot_info);

    return traverse_maze(path_grid,robot_info);
}

int main(void)
{
    int path_grid[] =
    {
        0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,0,1,1,1,0,1,0,0,0,
        0,0,1,0,0,0,1,0,1,1,1,0,
        0,0,1,0,1,1,1,1,1,0,1,0,
        0,0,1,0,1,0,0,0,1,0,1,0,
        0,1,1,1,1,0,1,0,1,1,0,0,
        0,0,1,0,1,1,1,1,0,1,0,0,
        0,1,1,0,1,0,1,0,1,1,0,0,
        0,1,0,0,1,0,1,0,0,1,1,0,
        0,1,1,1,1,0,1,0,1,1,0,0,
        0,0,1,0,0,0,0,1,1,0,0,0,        
        0,0,0,0,0,0,0,0,2,0,0,0,
    };
                    
    initialize_maze(path_grid);
    foreground();
    setColour(green);
    struct robot my_robot = {40,80,40,120,80,100,'e'};

    draw_robot(my_robot);
    sleep(500);
    my_robot = traverse_maze(path_grid,my_robot);

    return 0;
}

# C Coursework

## Overview

My coursework implements a drawing program that displays and animates a robot moving around a rectangular maze, starting at the entrance and finishing at the exit.

## What I did

Using the *drawapp-2.0* program, my code displays a maze in the **background()** via an array, and a robot in the **foreground()**.  
The robot can move left right and forward via functions that update it's coordinates. Functions also determine its location in relation to walls and the exit by calculating the array position of the square the robot points to.  
The **traverse_maze()** function uses recursion to navigate the maze. It moves forward until reaching a wall, then prioritizes turning right over left, until the exit is reached.

```c
    if(can_move(path_grid,robot_info) == 0)
    {
        robot_info = right(robot_info);

        if(can_move(path_grid,robot_info) == 0)
        {
            robot_info = left(robot_info);
            robot_info = left(robot_info);
        }
    }
```

## How to execute

Type the following into the command line.  
Compile the code before running.

##### to compile the code:

> gcc .\maze.c .\graphics.c 

##### to run the code:

> .\a.exe | java -jar .\drawapp-2.0.jar  
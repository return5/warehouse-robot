//------------------------- Description ------------------------------
//Program to control a robot througbh a warehouse.
//use the simple commands to move the robot around the boxes to reach the goal.

//------------------------- License ----------------------------------
//  license: GPL 3.0        Author: github/return5
//
//  Copyright (C) <2020>  <return5>
//
//  This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//-------------------------- includes -------------------------------------- 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "movement.h"
#include "window.h"
#include "commands.h"
#include "controlls.h"
#include "obj.h"
#include "params.h"
#include "read_file.h"

//-------------------------- function declerations ------------------------- 

static void gameLoop(ROBOT_S *const robot, NODE *head);
static void loadNewLevel(ROBOT_S *const robot,NODE *head);
static void initGame(void);
static void printStuff(const ROBOT_S *const robot);

//-------------------------- global vars -----------------------------------
int PLAY = 1;
static int MAX_LEVELS,CURRENT_LEVEL;
//-------------------------- functions -------------------------------------


static void loadNewLevel(ROBOT_S *const robot,NODE *head) {
    cleanUpArray();
    initGame();
    printStuff(robot);
    PLAY = 1;
    head = NULL; 
    gameLoop(robot,head);
}

static void gameLoop(ROBOT_S *const robot, NODE *head) {
	while(PLAY) {
		head = getUserInput(head,robot);
	}
    CURRENT_LEVEL++;
    if(CURRENT_LEVEL <= MAX_LEVELS) {
        loadNewLevel(robot,head);
    }
}

static void initGame(void) {
    makeObjArray();
    readLevelData(CURRENT_LEVEL);
    START_DIR = UP;
	OBJECTS->objects[0]->color = GREEN_C; //make finish goal green
	OBJECTS->objects[0]->goal  = 1;
	makeObjectWindows();
}

static void printStuff(const ROBOT_S *const robot) {
    printRobot(robot);
	printObjectWindows();
}

int main(void) {
    MAX_LEVELS    = 1;
    CURRENT_LEVEL = 2;
	srand(time(0));
	startNcurses();
    initGame();
    initWindows();
	ROBOT_S robot = {START_X,START_Y,START_DIR};
	NODE *head = NULL;
    printStuff(&robot);
	gameLoop(&robot,head);
	endwin();
	return EXIT_SUCCESS;
}

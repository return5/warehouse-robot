//-------------------------- Description -----------------------------------
//File contains all the functions to control the movement of the robot. 
//-------------------------- includes -------------------------------------- 
#include <stdio.h>
#include "collision.h"
#include "movement.h"
#include "params.h"

//-------------------------- function declerations ------------------------- 
static int moveUp(const int y);
static DIRECTION turnRobotCCW(const DIRECTION dir);
static DIRECTION turnRobotCW(const DIRECTION dir);
static void moveRobot(ROBOT_S *const robot);
static int moveRight(const int x);
static int moveLeft(const int x);

//-------------------------- functions -------------------------------------

static int moveLeft(const int x) {
	const int new_x = x - 1;
	if(new_x > 0 ) {
		return new_x;
	}
	return x;
}

static int moveRight(const int x) {
	const int new_x = x + 1;
	if(new_x < WIDTH ) {
		return new_x;
	}
	return x;
}

static int moveUp(const int y) {
	const int new_y = y - 1;
	if(new_y > 0) {
		return new_y;
	}
	return y;
}


static int moveDown(const int y) {
	const int new_y = y + 1;
	if(new_y < HEIGHT) {
		return new_y;
	}
	return y;
}

static void moveRobot(ROBOT_S *const robot) {
	const int old_x = robot->x;
	const int old_y = robot->y;
	switch(robot->dir) {
		case UP: robot->y = moveUp(robot->y);
			break;
		case DOWN: robot->y = moveDown(robot->y);
			break;
		case LEFT: robot->x = moveLeft(robot->x);
			break;
		case RIGHT: robot->x = moveRight(robot->x);
			break;
		default:  //do nothing
			break;
	}
	if(checkForCollisions(robot)) {
		robot->x = old_x;
		robot->y = old_y;
	}
}

static DIRECTION turnRobotCCW(const DIRECTION dir) {
	DIRECTION new_dir;
	switch(dir) {
		case UP: new_dir = LEFT;
			break;
		case DOWN: new_dir = RIGHT;
			break;
		case LEFT: new_dir = DOWN;
			break;
		case RIGHT: new_dir = UP;
			break;
		default: new_dir = dir;
			break;
	}
	return new_dir;
}

static DIRECTION turnRobotCW(const DIRECTION dir) {
	DIRECTION new_dir;
	switch(dir) {
		case UP: new_dir = RIGHT;
			break;
		case DOWN: new_dir = LEFT;
		  	break;
		case LEFT: new_dir = UP;
			break;
		case RIGHT: new_dir = DOWN;
			break;
		default: new_dir = dir;
			break;
	}
	return new_dir;
}

void executeFunction(ROBOT_S *const robot,const FUNC func) {
	switch(func) {
		case MOVE: moveRobot(robot);
			break;
		case TURNCW: robot->dir = turnRobotCW(robot->dir);
			break;
		case TURNCCW: robot->dir = turnRobotCCW(robot->dir);
			break;
		case WAIT: //do nothing
			break;
		default:  //do nothing
			break;
	}
}

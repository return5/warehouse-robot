//-------------------------- Description -----------------------------------
//File contains the functions to create the LinkedList consisting of the commands for the robot.
//Also includes the function to iterate that LinkedList to execute the commands.
//-------------------------- includes --------------------------------------
#include <stdlib.h>
#include <time.h>
#include "commands.h"
#include "window.h"
#include "movement.h"
#include "params.h"

//-------------------------- global vars  -----------------------------------

static int PLAYER_MOVES = 0;

//-------------------------- function declerations ------------------------- 

static NODE *makeNode(const FUNC func);
static void updateStepsDisplay(const FUNC func);
static NODE *clearLinkedList(NODE *h);
static void checkIfGoal(const ROBOT_S *const robot);
//-------------------------- functions  ------------------------------------

int getPlayerMoves(void) {
    return PLAYER_MOVES;
}

static void checkIfGoal(const ROBOT_S *const robot) {
    if(robot->x > GOAL_LEFT && robot->x < GOAL_RIGHT - 3) {
        if(robot->y >= 2 && robot->y <= 4) {
            PLAY = 0;
            printPlayerScore(PLAYER_MOVES);
        }
    }
}

static NODE *clearLinkedList(NODE *head) {
	NODE *temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}

NODE *itCommands(ROBOT_S *const robot,const NODE *const head) {
	NODE *h = (NODE*) head;
	while(h != NULL) {
		executeFunction(robot,h->func);
		printRobot(robot);
		printObjectWindows();
		h = h->next;
		nanosleep((const struct timespec[]){{0, 400000000L}}, NULL);
        PLAYER_MOVES++;
	}
	clearStepsWin(); //when done with all commands, clear the step window
    checkIfGoal(robot);
	return clearLinkedList((NODE *)head);
}

static NODE *makeNode(const FUNC func) {
	NODE *node = malloc(SIZE_NODE);
	node->func = func;
	node->next = NULL;
	return node;
}

static void updateStepsDisplay(const FUNC func) {
	char *str;
	switch(func) {
		case MOVE: str ="move-> ";
			break;
		case TURNCCW: str = "Turn CCW-> ";
			break;
		case TURNCW: str = "Turn CCW-> ";
			break;
		case WAIT: str = "wait-> ";
			break;
		default: str = "wait-> ";
			break;
	}
	printToStepsWin(str);
}

NODE *addNode(const NODE *const head, const FUNC func) {
	NODE *new = makeNode(func);
	updateStepsDisplay(func);
	if(head == NULL) {
		return new;
	}
	NODE *h = (NODE*)head;
	while(h->next != NULL) {
		h = h->next;
	}
	h->next = new;
	return (NODE*)head;
}

NODE *resetSteps(NODE *head) {
	clearStepsWin();
	return clearLinkedList(head);
}

NODE *resetRobot(ROBOT_S *const robot,NODE *head) {
	robot->x     = START_X;
	robot->y     = START_Y;
	robot->dir   = START_DIR;
    PLAYER_MOVES = 0;
    printRobot(robot);
    printObjectWindows();
	return resetSteps(head);
}

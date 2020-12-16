//-------------------------- Description -----------------------------------
//This file contains the functions needed to process user inputs to the program.
//
//-------------------------- includes --------------------------------------
#include <ncurses.h>
#include "commands.h"
#include "controlls.h"
#include "params.h"
//-------------------------- global vars  -----------------------------------

//-------------------------- function declerations ------------------------- 
static NODE *checkIfButtonClicked(const int x, const int y,NODE *head,const ROBOT_S *const robot);

//-------------------------- functions  ------------------------------------

static NODE *checkIfButtonClicked(const int x, const int y,NODE *head,const ROBOT_S *const robot) {
	if(x >= MOVE_BTTN_X - 1 && x < MOVE_BTTN_X + 5) {
		if(y >= MOVE_BTTN_Y - 1 && y < MOVE_BTTN_Y + 2 ) {
			return addNode(head,MOVE);
		}
	}
	if(x >= TURNCC_BTTN_X - 1 && x < TURNCC_BTTN_X + 9) {
		if(y >= TURNCC_BTTN_Y - 1 && y < TURNCC_BTTN_Y + 2 ) {
			return addNode(head,TURNCCW);
		}
	}
	if(x >= TURNCW_BTTN_X - 1 && x < TURNCW_BTTN_X + 8) {
		if(y >= TURNCW_BTTN_Y - 1 && y < TURNCW_BTTN_Y + 2 ) {
			return addNode(head,TURNCW);
		}
	}
	if(x >= WAIT_BTTN_X - 1 && x < WAIT_BTTN_X + 5) {
		if(y >= WAIT_BTTN_Y - 1  && y < WAIT_BTTN_Y + 2 ) {
			return addNode(head,WAIT);
		}
	}
	if(x >= (START_BTTN_X) - 1 && x < (START_BTTN_X) + 6) {
		if(y >= START_BTTN_Y - 1  && y < START_BTTN_Y + 2 ) {
			return itCommands((ROBOT_S *)robot,head);
		}
	}
	if(x >= RESET_BTTN_X - 1 && x < RESET_BTTN_X + 6) {
		if(y >= RESET_BTTN_Y - 1  && y < RESET_BTTN_Y + 2 ) {
			return resetRobot((ROBOT_S *)robot,head);
		}
	}
	if(x >= CLEAR_BTTN_X - 1 && x < CLEAR_BTTN_X + 6) {
		if(y >= CLEAR_BTTN_Y - 1  && y < CLEAR_BTTN_Y + 2 ) {
			return resetSteps(head);
		}
	}
	if(x >= STOP_BTTN_X - 1 && x < STOP_BTTN_X + 5) {
		if(y >= STOP_BTTN_Y - 1  && y < STOP_BTTN_Y + 2 ) {
			PLAY = 0;
		}
	}
	return head;
}

NODE *getUserInput(NODE *head,const ROBOT_S *const robot) {
	MEVENT event;
	if(getch() == KEY_MOUSE) {
		if(getmouse(&event) == OK) {
			if(event.bstate & BUTTON1_CLICKED){
				head = checkIfButtonClicked(event.x,event.y,head,robot);
			}
		}
	}
	return head;
}

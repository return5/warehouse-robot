//-------------------------- Description -----------------------------------
//File contains all the functions relating to ncurses windows.
//Also contains the functions to initialize ncurses when program starts.
//
//-------------------------- includes --------------------------------------
#include <string.h>
#include <stdlib.h>
#include "params.h"
#include "window.h"
//-------------------------- global vars  -----------------------------------

static WINDOW *WINDOW_AR[6];       //array of the ncurses windows for this program
static WINDOW *BTTN_WINS[8];
static unsigned int WIN_COLUMN = 0;  //how far right to print the command in step window
static unsigned int WIN_ROW    = 0;  //how far down to print the command in step window

int START_X,START_Y,START_DIR,HEIGHT,WIDTH;

//-------------------------- function declerations ------------------------- 

static void initColors(void);
static WINDOW *constructWindow(const OBJ *const obj);
static void initScreen(void);
static void makeWindows(void);
static void refreshWins(void);
static void printBttnLabels(void);
static void makeFuncBttnWindows(void);
static void makeBttnBorder(const int h, const int w,const int x, const int y);
static void refreshBttnWins(void);

//-------------------------- functions  ------------------------------------


void printPlayerScore(const int moves) {
    wclear(MAIN_WINDOW);
    mvwprintw(MAIN_WINDOW,5,3,"congrats, you won!");
    mvwprintw(MAIN_WINDOW,6,3,"It took you %d steps to reach the goal.",moves);
    mvwprintw(MAIN_WINDOW,7,3,"Please,press any key to continue.");
    wrefresh(MAIN_WINDOW);
    getch();
}

static void refreshWins(void) {
	for(int i = 0; i < 6; i++) {
		wrefresh(WINDOW_AR[i]);
	}
}

static void refreshBttnWins(void) {
	for(int i = 0; i < 8; i++) {
		wrefresh(BTTN_WINS[i]);
	}
}

static void printBttnLabels(void) {
	wprintw(TURNCC_BTTN,"Turn_CCW");
	wprintw(TURNCW_BTTN,"Turn_CW");
	wprintw(WAIT_BTTN,"Wait");
	wprintw(MOVE_BTTN,"Move");
	wprintw(START_BTTN,"Start");
    wprintw(CLEAR_BTTN,"Clear");
	wprintw(RESET_BTTN,"Reset");
	wprintw(STOP_BTTN,"Exit");
}

static void makeBttnBorder(const int h, const int w,const int x, const int y) {
	WINDOW *tmp  = newwin(h,w,y,x);
	wborder(tmp,'|','|','-', '-', '+', '+', '+', '+');
	wrefresh(tmp);
}

static void makeFuncBttnWindows(void) {
	MOVE_BTTN   = newwin(1,4,MOVE_BTTN_Y,MOVE_BTTN_X);
	TURNCC_BTTN = newwin(1,8,TURNCC_BTTN_Y,TURNCC_BTTN_X);
	TURNCW_BTTN = newwin(1,7,TURNCW_BTTN_Y,TURNCW_BTTN_X);
	WAIT_BTTN   = newwin(1,4,WAIT_BTTN_Y,WAIT_BTTN_X);
	START_BTTN  = newwin(1,5,START_BTTN_Y,START_BTTN_X);
	CLEAR_BTTN  = newwin(1,5,CLEAR_BTTN_Y,CLEAR_BTTN_X);
	RESET_BTTN  = newwin(1,5,RESET_BTTN_Y,RESET_BTTN_X);
	STOP_BTTN   = newwin(1,4,STOP_BTTN_Y,STOP_BTTN_X);
	makeBttnBorder(3,10,TURNCC_BTTN_X - 1, TURNCC_BTTN_Y - 1);
	makeBttnBorder(3,9,TURNCW_BTTN_X - 1, TURNCW_BTTN_Y - 1);
	makeBttnBorder(3,6,MOVE_BTTN_X - 1, MOVE_BTTN_Y - 1);
	makeBttnBorder(3,6,WAIT_BTTN_X - 1, WAIT_BTTN_Y - 1);
	makeBttnBorder(3,7,START_BTTN_X - 1, START_BTTN_Y - 1);
	makeBttnBorder(3,7,CLEAR_BTTN_X - 1, CLEAR_BTTN_Y - 1);
	makeBttnBorder(3,7,RESET_BTTN_X - 1, RESET_BTTN_Y - 1);
	makeBttnBorder(3,6,STOP_BTTN_X - 1, STOP_BTTN_Y - 1);
}

static void makeWindows(void) {
	MAIN_WINDOW  = newwin(HEIGHT,WIDTH,1,1); 
	FUNC_WINDOW  = newwin(FUNC_W_H,FUNC_W_W,FUNC_W_Y,FUNC_W_X);	
	STEPS_WINDOW = newwin(STEPS_W_H,STEPS_W_W,STEPS_W_Y,STEPS_W_X);
	MAIN_BORDER  = newwin(HEIGHT + 2,WIDTH + 2,0,0);
	FUNC_BORDER  = newwin(FUNC_W_H + 2, FUNC_W_W + 2,FUNC_W_Y - 1, FUNC_W_X - 1);
	STEPS_BORDER = newwin(STEPS_W_H + 2, STEPS_W_W + 2,STEPS_W_Y - 1, STEPS_W_X - 1);
	wborder(MAIN_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wborder(FUNC_BORDER,'|','|','-', '-', '+', '+', '+', '+');
	wborder(STEPS_BORDER,'|','|','-', '-', '+', '+', '+', '+');
}

static WINDOW *constructWindow(const OBJ *const obj) {
	WINDOW *temp = newwin((obj->bottom - obj->top) + 1,(obj->right - obj->left) + 1,obj->top,obj->left);
	return temp;
}

void makeObjectWindows(void) {
	for(unsigned int i = 0; i < OBJECTS->length; i++) {
		OBJECTS->objects[i]->window = constructWindow(OBJECTS->objects[i]);
	}
}

static void printObjBackground(const OBJ *const obj) {
	for(int i = 0; i < obj->height;i++) {
		for(int j = 0; j < obj->width; j++) {
			mvwprintw(obj->window,i,j," ");
		}
	}
	if(obj->goal) {
		mvwprintw(obj->window,1,1,"goal");
	}
}

void printObjectWindows(void) {
	for(unsigned int i = 0; i < OBJECTS->length; i++) {
		wattron(OBJECTS->objects[i]->window,COLOR_PAIR(OBJECTS->objects[i]->color));
		printObjBackground(OBJECTS->objects[i]);
		wattroff(OBJECTS->objects[i]->window,COLOR_PAIR(OBJECTS->objects[i]->color));
		if(OBJECTS->objects[i]->goal != 1) {
			wborder(OBJECTS->objects[i]->window,'|','|','-', '-', '+', '+', '+', '+');
		}
		wrefresh(OBJECTS->objects[i]->window);
	}
}

//initializes ncruses
static void initScreen(void) {
	initscr();    //start ncuurses
	noecho();    //dont show user input on screen
	curs_set(0); //hide cursor
	keypad(stdscr,TRUE); //enable keypad. needed for mouse
	mousemask(ALL_MOUSE_EVENTS,NULL); //enable mouse input
}

static void initColors(void) {
	start_color();
	init_pair(MAGENTA_C,COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(YELLOW_C,COLOR_YELLOW,COLOR_YELLOW);
	init_pair(GREEN_C,COLOR_WHITE,COLOR_GREEN);  //color of finish goal
	init_pair(BLUE_C,COLOR_BLUE,COLOR_BLUE);	
	init_pair(CYAN_C,COLOR_CYAN,COLOR_CYAN);
	init_pair(RED_C,COLOR_RED,COLOR_RED);
	init_pair(WHITE_C,COLOR_WHITE,COLOR_WHITE);
	init_pair(9,COLOR_WHITE,COLOR_BLACK); //robot color
}

void startNcurses(void) {
	initScreen();
	initColors();
	refresh();
}

void initWindows(void) {
	makeWindows();
	refreshWins();
	makeFuncBttnWindows();
	printBttnLabels();
    refreshBttnWins();
}

void printRobot(const ROBOT_S *const robot) {
	wclear(MAIN_WINDOW);
	wattron(MAIN_WINDOW,COLOR_PAIR(9));
	mvwprintw(MAIN_WINDOW,robot->y-1,robot->x,"%c",ROBOT_HEAD);
	mvwprintw(MAIN_WINDOW,robot->y,robot->x,"%c", ROBOT_BODY);
	mvwprintw(MAIN_WINDOW,robot->y,robot->x-1,"%c",ROBOT_LARM);
	mvwprintw(MAIN_WINDOW,robot->y,robot->x+1,"%c",ROBOT_RARM);
	mvwprintw(MAIN_WINDOW,robot->y+1,robot->x,"%c",ROBOT_LEGS);
	wrefresh(MAIN_WINDOW);
	wattroff(MAIN_WINDOW,COLOR_PAIR(9));

}

//prints a command to step window.
//WIN_COLUMN and WIN_ROw are used to set the correct location of the command string.
void printToStepsWin(const char *const str) {
	const int len = strlen(str);
	if(WIN_COLUMN + len > STEPS_W_W) {
		WIN_COLUMN = 0;
		WIN_ROW++;
	}
	mvwprintw(STEPS_WINDOW,WIN_ROW,WIN_COLUMN,"%s",str);
	wrefresh(STEPS_WINDOW);
	WIN_COLUMN += len;
}

//clears the step window of all old steps once the robot is finished.
void clearStepsWin(void) {
	wclear(STEPS_WINDOW);
	wrefresh(STEPS_WINDOW);
	WIN_COLUMN = WIN_ROW = 0;   //reset these back to zero.
}

void cleanUpWindow(OBJ *const window) {
    wclear(window->window);
    wrefresh(window->window);
    delwin(window->window);
}



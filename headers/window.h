#ifndef WINDOW_M
#define WINDOW_M
//-------------------------- includes --------------------------------------
#include <ncurses.h>
#include "robot.h"
#include "obj.h"
//-------------------------- macros ----------------------------------------

//-------------------------- function declerations ------------------------- 

void startNcurses(void);
void printRobot(const ROBOT_S *const robot);
void printToStepsWin(const char *const str);
void clearStepsWin(void);
void makeObjectWindows(void);
void printObjectWindows(void);
void printPlayerScore(const int moves);
void initWindows(void);
void cleanUpWindow(OBJ *const window);
#endif


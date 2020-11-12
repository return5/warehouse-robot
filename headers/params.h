/*  various parameters and macros used in this program. */

#ifndef PARAMS_M
#define PARAMS_M
//-------------------------- includes --------------------------------------

//-------------------------- macros ----------------------------------------

//paramters for the three main windows
#define FUNC_W_H 6                //height of func_w
#define FUNC_W_W 43              //width of func_w
#define FUNC_W_Y HEIGHT + 4     //starting x  of func_w
#define FUNC_W_X 1             //stating y of func_w
#define STEPS_W_H HEIGHT    
#define STEPS_W_W 31
#define STEPS_W_Y 1
#define STEPS_W_X WIDTH + 4

//shortcuts to access the three windows inside the window array
#define MAIN_WINDOW WINDOW_AR[0]
#define FUNC_WINDOW WINDOW_AR[1]
#define STEPS_WINDOW WINDOW_AR[2]
#define MAIN_BORDER WINDOW_AR[3]
#define FUNC_BORDER WINDOW_AR[4]
#define STEPS_BORDER WINDOW_AR[5]

//shortcuts for accessing the button windows inside the array
#define MOVE_BTTN BTTN_WINS[0]
#define TURNCC_BTTN BTTN_WINS[1]
#define TURNCW_BTTN BTTN_WINS[2]
#define WAIT_BTTN BTTN_WINS[3]
#define START_BTTN BTTN_WINS[4]
#define RESET_BTTN BTTN_WINS[5]
#define STOP_BTTN BTTN_WINS[6]
#define CLEAR_BTTN BTTN_WINS[7]

//parameters for the button windows
#define MOVE_BTTN_X (FUNC_W_X + 4)
#define MOVE_BTTN_Y (FUNC_W_Y + 1)
#define TURNCC_BTTN_X (MOVE_BTTN_X + 8)
#define TURNCC_BTTN_Y (MOVE_BTTN_Y)
#define TURNCW_BTTN_X (TURNCC_BTTN_X + 12)
#define TURNCW_BTTN_Y (MOVE_BTTN_Y)
#define WAIT_BTTN_X (TURNCW_BTTN_X  + 11)
#define WAIT_BTTN_Y (MOVE_BTTN_Y)
#define START_BTTN_X (MOVE_BTTN_X)
#define START_BTTN_Y (MOVE_BTTN_Y + 3)
#define CLEAR_BTTN_X (START_BTTN_X + 9)
#define CLEAR_BTTN_Y (START_BTTN_Y)
#define RESET_BTTN_X (CLEAR_BTTN_X + 9)
#define RESET_BTTN_Y (START_BTTN_Y)
#define STOP_BTTN_X (RESET_BTTN_X + 9)
#define STOP_BTTN_Y (START_BTTN_Y)

//the robot icon
#define ROBOT_HEAD 'o'
#define ROBOT_LARM '<'
#define ROBOT_RARM '>'
#define ROBOT_BODY '='
#define ROBOT_LEGS 'L'

//goal location
#define GOAL_LEFT ((WIDTH/2) - 3)
#define GOAL_RIGHT ((WIDTH/2) + 3)

//-------------------------- global vars -----------------------------------
extern int PLAY,START_X,START_Y,START_DIR,HEIGHT,WIDTH;
//-------------------------- function declerations ------------------------- 

#endif


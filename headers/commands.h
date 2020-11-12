//--------------------------- include guards --------------------------------
#ifndef COMMAND_M
#define COMMAND_M

//--------------------------- headers ---------------------------------------
#include "robot.h"

//---------------------------  MACROS ---------------------------------------
#define SIZE_NODE sizeof(NODE)

//-------------------------- enums, structs, and typedefs -------------------
enum FUNCTIONS_E {MOVE,TURNCW,TURNCCW,WAIT};

typedef enum FUNCTIONS_E FUNC;
typedef struct NODE NODE;

struct NODE {  //nodes for the linked list. used to hold the commands for the robot.
    FUNC func;
    NODE *next;
};


//-------------------------- function declerations ------------------------- 
NODE *addNode(const NODE *const head, const FUNC func);
NODE *itCommands(ROBOT_S *const robot, const NODE *const head);
NODE *resetSteps(NODE *head);
NODE *resetRobot(ROBOT_S *const robot,NODE *head);
int getPlayerMoves(void);
#endif


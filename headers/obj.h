
//--------------------------- include guards --------------------------------
#ifndef OBJ_M
#define OBJ_M
//--------------------------- headers ---------------------------------------
#include <ncurses.h>
//---------------------------  MACROS ---------------------------------------

//-------------------------- enums, structs, and typedefs -------------------

enum COLORS { MAGENTA_C = 1,WHITE_C,YELLOW_C,GREEN_C,BLUE_C,CYAN_C,RED_C,NUM};

typedef enum COLORS COLOR;

typedef struct OBJ {
    int left,right,top,bottom,width,height,goal;
    WINDOW *window;
    COLOR color;
}OBJ;

typedef struct OBJ_ARRAY {
    OBJ **objects;
    unsigned int length,max_size;
}OBJ_ARRAY;


//-------------------------- global vars ----------------------------------
extern OBJ_ARRAY *OBJECTS;
//-------------------------- function declerations ------------------------- 
void loadObjects(void);
void addNewWindow(const int x, const int y, const int height, const int width);
void makeObjArray(void);
void cleanUpArray(void);
#endif


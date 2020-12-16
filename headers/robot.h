#ifndef ROBOT_M
#define ROBOT_M

enum DIRECTION_E {UP,DOWN,LEFT,RIGHT};

typedef enum DIRECTION_E DIRECTION;

typedef struct ROBOT_S {
    int        x,y;
    DIRECTION  dir;
}ROBOT_S;

#endif


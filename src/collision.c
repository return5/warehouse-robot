//-------------------------- Description -----------------------------------
//File contains all the functions needed to check for collison between robot and object.
//-------------------------- includes --------------------------------------
#include "obj.h"
#include "collision.h"
//-------------------------- global vars  -----------------------------------
//-------------------------- function declerations -------------------------- 
static int checkCollision(const ROBOT_S *const robot,const OBJ *const obj);

//-------------------------- functions  -------------------------------------

static int checkCollision(const ROBOT_S *const robot, const OBJ *const obj) {
	if(!obj->goal) {
		if(robot->y <= obj->bottom && robot->y + 2 >= obj->top) {
			if(robot->x <= obj->right && robot->x + 2 >= obj->left) {
				return 1;
			}
		}
	}
	return 0;
}

int checkForCollisions(const ROBOT_S *const robot) {
	for(unsigned int i = 0; i < OBJECTS->length;i++) {
		if(checkCollision(robot,OBJECTS->objects[i])) {
			return 1;
		}
	}
	return 0;
}

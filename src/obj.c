
//-------------------------- Description -----------------------------------
//
//-------------------------- includes --------------------------------------
#include <stdlib.h>
#include "obj.h"
#include "window.h"
#include "params.h"
//-------------------------- global vars  -----------------------------------
OBJ_ARRAY *OBJECTS;
//-------------------------- function declerations ------------------------- 
void makeObjArray(void);
static OBJ *makeObjStruct(const int top,const int left,const int width,const int height);
static COLOR getColor(void);
//-------------------------- functions  ------------------------------------

//get a random color for the object
static COLOR getColor(void) {
	switch(rand() % NUM) {
		case 0: return MAGENTA_C;
		case 1: return YELLOW_C;
		case 2: return WHITE_C;
		case 3: return BLUE_C;
		case 4: return CYAN_C;
		case 5: return RED_C;
		default: return MAGENTA_C;
	}
}

void makeObjArray(void) {
	OBJECTS           = malloc(sizeof(OBJ_ARRAY));
	OBJECTS->length   = 0;
	OBJECTS->max_size = 5;
	OBJECTS->objects  = malloc(sizeof(OBJ) * OBJECTS->max_size);
}

static OBJ *makeObjStruct(const int top, const int left, const int width, const int height) {
	OBJ *temp    = malloc(sizeof(OBJ));
	temp->top    = top;
	temp->bottom = top + height;
	temp->left   = left;
	temp->right  = left + width;
	temp->width  = width;
	temp->height = height;
	temp->goal   = 0;
	temp->color  = getColor();
	return temp;
}

static void checkSizeArray(void) {
    if(OBJECTS->length > OBJECTS->max_size) {
        OBJECTS->max_size += 5;
        OBJ **temp = realloc(OBJECTS->objects,sizeof(OBJ) * OBJECTS->max_size);
        if(temp == NULL) {
            temp = realloc(OBJECTS->objects,sizeof(OBJ) * OBJECTS->max_size);
        }
        OBJECTS->objects = temp;
    }
}

void addNewWindow(const int x, const int y, const int height, const int width) {
    checkSizeArray();
    OBJECTS->objects[OBJECTS->length] = makeObjStruct(y,x,width,height);
    OBJECTS->length++;
}

void cleanUpArray(void) {
    for(unsigned int i = 0; i < OBJECTS->length; i++) {
        cleanUpWindow(OBJECTS->objects[i]);
        free(OBJECTS->objects[i]);
    }
    free(OBJECTS);
}


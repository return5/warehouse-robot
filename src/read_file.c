/*                                           ### description ###                       
    file contains functions for reading level data from a file  
*/

//---------------------------------------------- headers -------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "window.h"
#include "params.h"
#include "obj.h"
#include "read_file.h"
//---------------------------------------------- define --------------------------------------------------

//---------------------------------------------- enums ---------------------------------------------------


//---------------------------------------------- typedefs ------------------------------------------------


//---------------------------------------------- structs -------------------------------------------------


//---------------------------------------------- global vars ---------------------------------------------


//---------------------------------------------- prototypes ----------------------------------------------
static void readTwoValues(int *const a, int *const b, const FILE *const file);
static void readWindows(const FILE *const file);

//---------------------------------------------- code ----------------------------------------------------

static void readWindows(const FILE *const file) {
    char *str   = NULL;
    size_t buff = 0;
    const char del[2] =",";
    while(getline(&str,&buff,file) != -1) {
        const int y = atoi(strtok(str,del));
        const int x = atoi(strtok(NULL,del));
        const int w = atoi(strtok(NULL,del));
        const int h = atoi(strtok(NULL,del));
        addNewWindow(x,y,h,w);
        free(str);
        buff = 0;
    }
}

//read two ints from file.store the values inside 'a' and 'b'
static void readTwoValues(int *const a, int *const b,const FILE *const file) {
    char *line        = NULL;
    size_t buff       = 0;
    const char del[2] = ",";
    getline(&line,&buff,(FILE *)file);
    *a = atoi(strtok(line,del));
    *b = atoi(strtok(NULL,del));
    free(line);
}

void readLevelData(const int level_num) {
    char level[25];
    snprintf(level,25,"./levels/level_%d.dat",level_num);
    const FILE *const file = fopen(level,"r");
    readTwoValues(&HEIGHT,&WIDTH,file);
    readTwoValues(&START_Y,&START_X,file);
    readWindows(file);
    fclose((FILE *)file);
}



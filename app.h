#ifndef APP_H
#define APP_H
#include "toolSDL.h"
#include "WFC.h"
struct app;
typedef struct app *App;

struct map;
typedef struct map *Map;

App appConstructer();
void generateBord(char bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE]);

mainLoop(App aApp);


#endif

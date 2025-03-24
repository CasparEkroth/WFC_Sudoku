#ifndef APP_H
#define APP_H
#include "toolSDL.h"
#include "WFC.h"
struct app;
typedef struct app *App;

struct map;
typedef struct map *Map;

#define TILE_SIZE 32*2

App appConstructer();
Map mapConstructer(TTF_Font *pFont,SDL_Renderer *pRendrerer);

void destroyApp(App aApp);

void generateBord(int bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE]);

void appLoop(App aApp);

void mapCleanBord(Map aMap);


#endif

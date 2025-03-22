#include "app.h"

struct map{
    char borde[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
    SDL_Rect rect_bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
};

struct app{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderere;
    bool keys[SDL_NUM_SCANCODES];
    SDL_Point mouse_pos;
    bool programIsRunning;
    TTF_Font *pFont;
    struct map *aMap;
};

Map mapConstructer(){

}

App appConstructer(){
    App aApp = malloc(sizeof(struct app));
    initialize_window(aApp->pRenderere,aApp->pWindow,aApp->pFont);
    generateBord(aApp->aMap->borde);
    memset(aApp->keys, 0,sizeof(aApp->keys));
    aApp->programIsRunning = true;
    aApp->mouse_pos =(SDL_Point){0,0};

}


void generateBord(char bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE]){
    Wfc theWFC;
    theWFC = newWFC();
    runAlgo(theWFC, true);
    printWFC(theWFC);
    getBord(theWFC,bord);
    destroyWFC(theWFC);
}

mainLoop(App aApp){

}

void destroyApp(App aApp){
    destroyMap(aApp->aMap);
    free(aApp);
}

void destroyMap(Map aMap){
    free(aMap);
}
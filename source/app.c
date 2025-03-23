#include "app.h"

struct map{
    bool generateNewMap;
    int borde[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
    SDL_Rect rect_bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
    SDL_Texture *numbers[MAX_ENTROPI];
};

struct app{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderere;
    TTF_Font *pFont;
    bool keys[SDL_NUM_SCANCODES];
    SDL_Point mouse_pos;
    bool programIsRunning;
    struct map *aMap;
};

void generateBord(int bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE]){
    Wfc theWFC;
    theWFC = newWFC();
    runAlgo(theWFC, true);
    //printWFC(theWFC);
    getBord(theWFC,bord);
    destroyWFC(theWFC);
}

Map mapConstructer(TTF_Font *pFont,SDL_Renderer *pRendrerer){
    Map aMap = malloc(sizeof(struct map));
    generateBord(aMap->borde);//WFC
    for (int y = 0; y < MAP_SIZE_SIDE; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            aMap->rect_bord[y][x].h = TILE_SIZE;
            aMap->rect_bord[y][x].w = TILE_SIZE;
            aMap->rect_bord[y][x].x = (x * TILE_SIZE);
            aMap->rect_bord[y][x].y = (y * TILE_SIZE);
        }
    }
    aMap->generateNewMap = false;
    SDL_Rect temp ={0,0,TILE_SIZE,TILE_SIZE};
    for (int i = 0; i < MAX_ENTROPI; i++){
        char buffer[NAME]={0};
        addIntToString(buffer,(i+1));
        trimWhitespace(buffer);
        aMap->numbers[i] = textToScreen(buffer,pFont,pRendrerer,&temp);
    }
    return aMap;
}

App appConstructer(){
    App aApp = malloc(sizeof(struct app));
    initialize_window(&aApp->pRenderere,&aApp->pWindow,&aApp->pFont);
    memset(aApp->keys, 0,sizeof(aApp->keys));
    aApp->programIsRunning = true;
    aApp->mouse_pos =(SDL_Point){0,0};
    aApp->aMap = mapConstructer(aApp->pFont,aApp->pRenderere);
    return aApp;
}

void mapRender(Map aMap,SDL_Renderer *pRederer){
    for (int y = 0; y < MAP_SIZE_SIDE; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){            
            SDL_SetRenderDrawColor(pRederer,255,255,255,255);
            SDL_RenderDrawRect(pRederer,&aMap->rect_bord[y][x]);
            SDL_SetRenderDrawColor(pRederer,0,0,0,0);
            SDL_RenderCopy(pRederer,aMap->numbers[aMap->borde[y][x]-1],NULL,&aMap->rect_bord[y][x]);
        }
    }
}

void appInput(App aApp, SDL_Event event){
    // mouse
    while (SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_QUIT:
            aApp->programIsRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            aApp->keys[event.button.button] = SDL_PRESSED;
            break;
        case SDL_MOUSEBUTTONUP:
            aApp->keys[event.button.button] = SDL_RELEASED;
            break;
        case SDL_KEYDOWN:
            aApp->keys[event.key.keysym.scancode]  = true;
            break;
        case SDL_KEYUP:
            aApp->keys[event.key.keysym.scancode]  = false;
            break;
        default:
            break;
        }
    }
    if(aApp->keys[SDL_SCANCODE_G]) aApp->aMap->generateNewMap = true;
}

void appRenderer(App aApp){
    SDL_RenderClear(aApp->pRenderere);
    mapRender(aApp->aMap,aApp->pRenderere);
    SDL_RenderPresent(aApp->pRenderere);
}

void appUpdate(App aApp){
    if(aApp->aMap->generateNewMap){
        generateBord(aApp->aMap->borde);
        aApp->aMap->generateNewMap = false;
    }
}

void appLoop(App aApp){
    SDL_Event event = {0};
    while (aApp->programIsRunning){
        appInput(aApp,event);
        appUpdate(aApp);
        appRenderer(aApp);
    }
    destroyApp(aApp);
}

void destroyMap(Map aMap){
    for(int i = 0;i < MAX_ENTROPI;i++) 
        SDL_DestroyTexture(aMap->numbers[i]);
    free(aMap);
}

void destroyApp(App aApp){
    destroyMap(aApp->aMap);
    close_SDL(aApp->pWindow,aApp->pRenderere,aApp->pFont);
    free(aApp);
}


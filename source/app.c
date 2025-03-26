#include "app.h"

struct map{
    bool generateNewMap;
    int borde[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
    SDL_Rect rect_bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
    SDL_Rect quadrant[SIDE_NUM_QUADRANT][SIDE_NUM_QUADRANT];
    SDL_Texture *numbers[MAX_ENTROPI];
};

struct menu{
    //SDL_Rect menuBlocks;
    SDL_Rect selectNumber[MAX_ENTROPI];
    int selected_tile;
};

struct app{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderere;
    TTF_Font *pFont;
    bool keys[SDL_NUM_SCANCODES];
    SDL_Point mouse_pos,theTile;
    bool programIsRunning,updateTile;
    struct map *aMap;
    struct menu *aMenu;
};

void generateBord(int bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE]){
    Wfc theWFC;
    theWFC = newWFC();
    runAlgo(theWFC, true);
    //printWFC(theWFC);
    getBord(theWFC,bord);
    destroyWFC(theWFC);
}

Menu menuConstructer(SDL_Point startingPoint){
    Menu aMenu = malloc(sizeof(struct menu));
    aMenu->selected_tile = 0;
    for (int i = 0; i < MAX_ENTROPI; i++){
        aMenu->selectNumber[i].h = TILE_SIZE;
        aMenu->selectNumber[i].w = TILE_SIZE;
        aMenu->selectNumber[i].x = startingPoint.x;
        aMenu->selectNumber[i].y = startingPoint.y+(TILE_SIZE*i);
    }
    return aMenu;
}

Map mapConstructer(TTF_Font *pFont,SDL_Renderer *pRendrerer){
    Map aMap = malloc(sizeof(struct map));
    generateBord(aMap->borde);//WFC
    mapCleanBord(aMap);
    for (int y = 0; y < MAP_SIZE_SIDE; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            aMap->rect_bord[y][x].h = TILE_SIZE;
            aMap->rect_bord[y][x].w = TILE_SIZE;
            aMap->rect_bord[y][x].x = (x * TILE_SIZE);
            aMap->rect_bord[y][x].y = (y * TILE_SIZE);
        }
    }
    for (int y = 0; y < SIDE_NUM_QUADRANT ;y++){
        for(int x = 0; x < SIDE_NUM_QUADRANT;x++){
            int blockY = y*3;
            int blockX = x*3;
            aMap->quadrant[y][x].y = aMap->rect_bord[blockY][blockX].y;
            aMap->quadrant[y][x].x = aMap->rect_bord[blockY][blockX].x;
            aMap->quadrant[y][x].w = (TILE_SIZE*3);
            aMap->quadrant[y][x].h = (TILE_SIZE*3);
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
    aApp->updateTile = false;
    aApp->theTile = (SDL_Point){0,0};
    aApp->mouse_pos = (SDL_Point){0,0};
    aApp->aMap = mapConstructer(aApp->pFont,aApp->pRenderere);
    SDL_Point startingPoint = {aApp->aMap->rect_bord[0][MAP_SIZE_SIDE-1].x+TILE_SIZE*2,
                                aApp->aMap->rect_bord[0][MAP_SIZE_SIDE-1].y};
    aApp->aMenu = menuConstructer(startingPoint);
    return aApp;
}

void menuRender(Menu aMenu, Map aMap, SDL_Renderer *pRenderer){
    for (int i = 0; i < MAX_ENTROPI; i++){
        if(i == aMenu->selected_tile-1){
            SDL_SetRenderDrawColor(pRenderer,255,0,0,255);
            SDL_RenderDrawRect(pRenderer,&aMenu->selectNumber[i]);
            SDL_SetRenderDrawColor(pRenderer,0,0,0,0);
        } 
        SDL_RenderCopy(pRenderer,aMap->numbers[i],NULL,&aMenu->selectNumber[i]);
    }
}

void mapRender(Map aMap,SDL_Renderer *pRederer){
    for (int y = 0; y < MAP_SIZE_SIDE; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){            
            SDL_SetRenderDrawColor(pRederer,255,255,255,255);
            SDL_RenderDrawRect(pRederer,&aMap->rect_bord[y][x]);
            SDL_SetRenderDrawColor(pRederer,0,0,0,0);
            if(aMap->borde[y][x] == 0) continue;
            SDL_RenderCopy(pRederer,aMap->numbers[aMap->borde[y][x]-1],NULL,&aMap->rect_bord[y][x]);
        }
    }
    SDL_SetRenderDrawColor(pRederer,255,0,0,255);
    for (int y = 0; y < SIDE_NUM_QUADRANT ;y++){
        for(int x = 0; x < SIDE_NUM_QUADRANT;x++){
            SDL_RenderDrawRect(pRederer,&aMap->quadrant[y][x]);
        }
    }
    SDL_SetRenderDrawColor(pRederer,0,0,0,0);
}

void appInput(App aApp, SDL_Event event){
    SDL_Point mouse = {0};
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    if(mouseState){}
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
    for (int i = 0; i < MAX_ENTROPI; i++){
        if(pointInRect(aApp->aMenu->selectNumber[i],mouse) && mouseState){
            aApp->aMenu->selected_tile = i+1;
        }
    }
    for (int y  = 0; y   < MAP_SIZE_SIDE; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            if(pointInRect(aApp->aMap->rect_bord[y][x],mouse) && mouseState){
                aApp->theTile = (SDL_Point){x,y};
                aApp->updateTile = true;
            }
        }
    }
}

void appRenderer(App aApp){
    SDL_RenderClear(aApp->pRenderere);
    mapRender(aApp->aMap,aApp->pRenderere);
    menuRender(aApp->aMenu,aApp->aMap,aApp->pRenderere);
    SDL_RenderPresent(aApp->pRenderere);
}

void appUpdate(App aApp){
    if(aApp->aMap->generateNewMap){
        generateBord(aApp->aMap->borde);
        mapCleanBord(aApp->aMap);
        aApp->aMap->generateNewMap = false;
    }
    if(aApp->updateTile){
        aApp->aMap->borde[aApp->theTile.y][aApp->theTile.x] = aApp->aMenu->selected_tile;
        aApp->updateTile = false; 
    }
}

void mapCleanBord(Map aMap){
    for (int y  = 0; y   < SIZE_OF_QUADRANT; y++){
        for (int x = 0; x < SIZE_OF_QUADRANT; x++){
            int countOfTils = rand() % 4 + 5; 
            int removed = 0;
            while (removed < countOfTils){
                int dy = rand() % 3;
                int dx = rand() % 3;

                int row = y * 3 + dy;
                int col = x * 3 + dx;

                if (aMap->borde[row][col] != 0){
                    aMap->borde[row][col] = 0;
                    removed++;
                }
            }
        }
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

void destroyMenu(Menu aMenu){
    free(aMenu);
}

void destroyApp(App aApp){
    destroyMenu(aApp->aMenu);
    destroyMap(aApp->aMap);
    close_SDL(aApp->pWindow,aApp->pRenderere,aApp->pFont);
    free(aApp);
}


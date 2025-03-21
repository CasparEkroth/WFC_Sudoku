#include <stdio.h> 
#include "WFC.h"

typedef struct Point{
    int x;
    int y;
}Point;

struct tile{
    int container[MAX_ENTROPI];
    int entropi;
    bool isCollapst;
    int value;
};

struct wfc{
    struct tile *tiles[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
    void (*collapse)(struct tile *self);  // funktionspekare som tar en tile*
    int LowestEntrepi;
    struct Point lowIndex,ruleIndex;
};

Tile newTile(void){
    Tile aTile = malloc(sizeof(struct tile));
    if (!aTile){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    aTile->entropi = MAX_ENTROPI;
    aTile->isCollapst = false;
    aTile->value = -1;
    for (int i = 0; i < MAX_ENTROPI; i++){
        aTile->container[i] = (i + 1); // möjliga tal (void *)(intptr_t)
    }
    return aTile;
}

WFC newWFC(void){
    WFC aWFC = malloc(sizeof(struct wfc));
    aWFC->collapse = collapseTile;
    for (int y = 0; y < MAP_SIZE_SIDE; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            aWFC->tiles[y][x] = newTile();
        }
    }
    aWFC->lowIndex.x = 0;
    aWFC->lowIndex.y = 0;
    aWFC->ruleIndex.x = 0;
    aWFC->ruleIndex.y = 0;
    return aWFC;
}

//############# rules for tiles only for suduko #######

void threeThree(WFC aWFC){
    struct Point Quadrant ={0};
    Quadrant.x = aWFC->ruleIndex.x / 3;
    Quadrant.y = aWFC->ruleIndex.y / 3;
    for (int y = 0; y < SIZE_OF_QUADRANT; y++){
        for (int x = 0; x < SIZE_OF_QUADRANT; x++){
            int tileY = Quadrant.y * 3 + y;
            int tileX = Quadrant.x * 3 + x;
            if(aWFC->tiles[tileY][tileX]->isCollapst){
                int value = aWFC->tiles[tileY][tileX]->value-1;
                aWFC->tiles[aWFC->ruleIndex.y][aWFC->ruleIndex.x]->container[value] = 0; 
            }
        }
    }
    
} 

void axis(WFC aWFC){
    for (int i = 0; i < MAP_SIZE_SIDE; i++){
        if(aWFC->tiles[i][aWFC->ruleIndex.x]->isCollapst){
            int value = aWFC->tiles[i][aWFC->ruleIndex.x]->value-1;
            aWFC->tiles[aWFC->ruleIndex.y][aWFC->ruleIndex.x]->container[value] = 0; 
        }
        if(aWFC->tiles[aWFC->ruleIndex.y][i]->isCollapst){
            int value = aWFC->tiles[aWFC->ruleIndex.y][i]->value-1;
            aWFC->tiles[aWFC->ruleIndex.y][aWFC->ruleIndex.x]->container[value] = 0; 
        }
    }
    
}

void updateContainer(WFC aWFC){
    for (int y = 0; y < MAP_SIZE_SIDE ; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            aWFC->ruleIndex.x = x;
            aWFC->ruleIndex.y = y;
            threeThree(aWFC);
            axis(aWFC);
        }
    }
}

//###############
void updateEntropi(WFC aWFC){
    for (int y = 0; y < MAP_SIZE_SIDE ; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
                aWFC->tiles[y][x]->entropi = 0;
            for (int i = 0; i < MAX_ENTROPI; i++){
                if(aWFC->tiles[y][x]->container[i] != 0) aWFC->tiles[y][x]->entropi++;
            }
        }
    }
}

void findLowestEntrepi(WFC aWFC){
    int lowest = MAX_ENTROPI;
    for (int y = 0; y < MAP_SIZE_SIDE ; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            if(lowest>aWFC->tiles[y][x]->entropi && !aWFC->tiles[y][x]->isCollapst){
                lowest = aWFC->tiles[y][x]->entropi;
                aWFC->lowIndex.x = x;
                aWFC->lowIndex.y = y;
            }
        }
    }
}

void collapseTile(Tile aTile){
    if(aTile->entropi == 0) return; 
    int slump = rand()% aTile->entropi + 1;
    int count = 0;
    for (int i = 0; i < MAX_ENTROPI; i++){
        if(aTile->container[i] != 0) count++;
        if(count == slump){
            aTile->entropi = 0;
            aTile->isCollapst = true;
            aTile->value = (int)aTile->container[i];
            if (aTile->value == 0) aTile->value = 2;
            return;
        }
    }
}

void printWFC(WFC aWFC){
    for (int y = 0; y < MAP_SIZE_SIDE ; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            printf("%d",aWFC->tiles[y][x]->value);
        }
        printf("\n");
    }
}

bool isCompleted(WFC aWFC){
    for (int y = 0; y < MAP_SIZE_SIDE ; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            if(!aWFC->tiles[y][x]->isCollapst) return false;
        }
    }
    return true;
}

void test(Tile aTile, int value){
    aTile->entropi = 0;
    aTile->isCollapst = true;
    aTile->value = value;
}


void runAlgo(WFC aWFC){
    int count = 0;
    /*
    test(aWFC->tiles[0][0],5);
    test(aWFC->tiles[0][1],3);
    test(aWFC->tiles[0][4],7);
    test(aWFC->tiles[1][0],6);
    */

    printWFC(aWFC);
    printf("\n\n\n");
    while (!isCompleted(aWFC)){
        updateContainer(aWFC);
        updateEntropi(aWFC);
        findLowestEntrepi(aWFC);
        collapseTile(aWFC->tiles[aWFC->lowIndex.y][aWFC->lowIndex.x]);
        if(count++ == 20000){
            printf("Out of time!!\n");
            return;
        }
    }
}

void destroyWFC(WFC aWFC){
    for (int y = 0; y < MAP_SIZE_SIDE ; y++){
        for (int x = 0; x < MAP_SIZE_SIDE; x++){
            destroyTile(aWFC->tiles[y][x]);
        }
    }
    free(aWFC);
}

void destroyTile(Tile aTile){
    free(aTile);
}

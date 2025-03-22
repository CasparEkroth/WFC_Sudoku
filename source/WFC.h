#ifndef WFC_H
#define WFC_H
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct wfc;
typedef struct wfc *Wfc;

struct tile;
typedef struct tile *Tile;

#define MAX_ENTROPI (9)
#define MAP_SIZE_SIDE 9
#define MAP_SIZE (MAP_SIZE_SIDE * MAP_SIZE_SIDE)
#define SIZE_OF_QUADRANT 3

Tile newTile(void);
void updateEntropi(Wfc aWFC);
void collapseTile(Tile aTile);
void destroyTile(Tile aTile);

Wfc newWFC(void);
void destroyWFC(Wfc aWFC);
void printWFC(Wfc aWFC);
bool isCompleted(Wfc aWFC);
//## rule
void threeThree(Wfc aWFC);
void axis(Wfc aWFC);
void updateContainer(Wfc aWFC);
//##

void runAlgo(Wfc aWFC, bool retry);
void test(Tile aTile, int value);
void reset(Wfc aWFC);
void getBord(Wfc aWFC,char bord[MAP_SIZE_SIDE][MAP_SIZE_SIDE]);


// för suduko

#endif

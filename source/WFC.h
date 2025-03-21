#ifndef WFC_H
#define WFC_H
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct wfc;
typedef struct wfc *WFC;

struct tile;
typedef struct tile *Tile;

Tile newTile(void);
void updateEntropi(WFC aWFC);
void collapseTile(Tile aTile);
void destroyTile(Tile aTile);

WFC newWFC(void);
void destroyWFC(WFC aWFC);
void printWFC(WFC aWFC);
bool isCompleted(WFC aWFC);
//## rule
void threeThree(WFC aWFC);
void axis(WFC aWFC);
void updateContainer(WFC aWFC);
//##

void runAlgo(WFC aWFC);
void test(Tile aTile, int value);


#define MAX_ENTROPI (9)
#define MAP_SIZE_SIDE 9
#define MAP_SIZE (MAP_SIZE_SIDE * MAP_SIZE_SIDE)
#define SIZE_OF_QUADRANT 3
// för suduko

#endif

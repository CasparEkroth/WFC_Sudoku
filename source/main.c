#include "toolSDL.h"
#include "WFC.h"
void dbg(void *pItem){
    printf("[%s]\n",(char *)pItem);
}



int main(int argc, char **argv){
    (void)argc;
    (void)argv;
    srand(time(NULL));
    WFC theWFC;
    theWFC = newWFC();
    runAlgo(theWFC);
    printWFC(theWFC);
    destroyWFC(theWFC);
    return 0;
}

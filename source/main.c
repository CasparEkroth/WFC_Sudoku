#include "toolSDL.h"
#include "app.h"
void dbg(void *pItem){
    printf("[%s]\n",(char *)pItem);
}



int main(int argc, char **argv){
    (void)argc;
    (void)argv;
    srand(time(NULL));
    App theApp;
    theApp = appConstructer();
    appLoop(theApp);
    return 0;
}

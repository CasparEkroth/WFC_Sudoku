#include "initSDL.h"

bool initialize_window(SDL_Renderer **ppRenderere, SDL_Window **ppWindow, TTF_Font **ppFont){ // Initialiserar SDL och skapar fönster
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0 || SDL_Init(SDL_INIT_AUDIO) < 0){
        fprintf(stderr, "Error initializing SDL. %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        fprintf(stderr,"SDL_mixer could not initialize! Mix_Error: %s\n",Mix_GetError());
        return false;
    }
    *ppWindow = SDL_CreateWindow(
        NULL, // Titel
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y 
        STARTING_WINDOW_WIDTH, 
        STARTING_WINDOW_HEIGHT, 
        SDL_WINDOW_RESIZABLE  // Flags
    );
    if (!*ppWindow) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    *ppRenderere = SDL_CreateRenderer(*ppWindow, -1, render_flags);
    if (!*ppRenderere) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        return false;
    }
    *ppFont = TTF_OpenFont("resources/Academy Engraved LET Fonts.ttf",24);
    if(!*ppFont){
        fprintf(stderr,"Error opening Font: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void close_SDL(SDL_Window* pWindow,SDL_Renderer *pRenderer, TTF_Font *pFont){ 
    if(pFont) TTF_CloseFont(pFont);
    if (pRenderer) SDL_DestroyRenderer(pRenderer);
    if (pWindow) SDL_DestroyWindow(pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


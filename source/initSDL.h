#ifndef INITSDL_H
#define INITSDL_H

#include <SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define STARTING_WINDOW_WIDTH 800 
#define STARTING_WINDOW_HEIGHT 600



bool initialize_window(SDL_Renderer *pRenderere, SDL_Window *pWindow, TTF_Font *pFont);
void close_SDL(SDL_Window* pWindow,SDL_Renderer *pRenderer, TTF_Font *pFont);


#endif
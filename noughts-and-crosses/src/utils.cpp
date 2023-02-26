#include "utils.h"
#include "constants.h"
#include "globals.h"
#include <SDL.h>
#include "colours.h"

void init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        exit(1);
    }
    else
    {
        gWindow = SDL_CreateWindow( "Noughts and Crosses", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == nullptr )
        {
            exit(1);
        }

        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
        if( gRenderer == nullptr )
        {
            exit(1);
        }

        SDL_SetRenderDrawColor( gRenderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF );

    }
}

void close()
{
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    SDL_Quit();
}


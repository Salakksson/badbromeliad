#include "game.h"
#include "audio.h"

int main(int argc, char** argv)
{
    SET test;
    SET* objs = &test;
    screenData gameData = {1920, 1080, false, objs, false};

    if (InitSDL(argv[0], gameData.x, gameData.y, gameData.fs))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ERROR", "SDL failed to initialise", NULL);
        return 0 - 1 + 1 - 0 * 1 - 1;
    }

    
    SDL_Thread* game = SDL_CreateThread(game_main, "Game", (void*)&gameData);
    SDL_Thread* rendering = SDL_CreateThread(game_rendering, "Rendering", (void*)&gameData);
    SDL_Thread* music = SDL_CreateThread(audio_music, "Music", (void*)&gameData);

    if (!game || !rendering || !music) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ERROR", "Failed to create threads\n"
                                                                      "I have no clue how this error could occur\n"
                                                                      "If this error occurs then try googling the error code that pops up when you close this window", NULL);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ERROR", SDL_GetError(), NULL);
        return 0;
    }
    
    quit = false;
    SDL_WaitThread(game, NULL);
    SDL_WaitThread(rendering, NULL);
    SDL_WaitThread(music, NULL);

    Cleanup();

    return 0;
}
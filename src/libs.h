#ifndef LIBS
#define LIBS
#define ASSETS_DIRECTORY "assets/"
#define PI 3.141592654

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

extern float ASPECT_RATIO;

typedef struct 
{
    Mix_Music* bg_p1;
    Mix_Music* bg_p2;
} musicPlayer;

extern musicPlayer mp3s;


// SDL Global
extern SDL_Window* window;
extern TTF_Font* font;
extern SDL_Color textColor;
extern SDL_GLContext GL;

extern SDL_mutex *listMutex;

bool inRangef(float low, float high, float x);

int InitSDL(char* name, int x, int y, bool fs);

void InitGL();

void InitTextures();

void Cleanup();

#endif
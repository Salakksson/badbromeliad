#ifndef GAMEOBJ
#define GAMEOBJ

#include "rect.h"

typedef struct TYPEDEF_GAMEOBJ
{   
    struct TYPEDEF_GAMEOBJ* prev;

    GLF_Rect* model;
    float dx, dy;

    struct TYPEDEF_GAMEOBJ* next;
}GameObj;

typedef struct
{
    GLF_Rect* BG;

    
    GameObj* player;
    
   

    GLF_Rect* GuiBox;
    GLF_Rect** text;
    int menuTextCount;

    GLF_Slider* slider;

    GLF_Rect* FPS;

    GameObj* enemies;

    GLF_Rect* hearts[3];

} SET;

GameObj* createObj(float x, float y, float w, float h, GLuint textureID, GameObj* prev);

void freeObj(GameObj* obj);

#endif
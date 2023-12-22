#ifndef RENDERING
#define RENDERING
#include "libs.h"
#include "gameobj.h"

// typedef struct
// {
//     float x, y, z;
//     float pitch, yaw;

// } Camera;

// extern Camera camera;

typedef struct
{
    int x, y;
    bool fs;
    SET* objs;
    bool reload;
}screenData;


// extern GLuint Texture_Ananas;
// extern GLuint Texture_BG;

extern bool* B_FPS;
extern bool* B_MENU;

void Render_DrawText(GLF_Text* text);

void GLF_DrawRect(GLF_Rect* rect);

void drawSlider(GLF_Slider* slider);

void Render_ScreenDraw(SET* objs);


#endif
#ifndef RECT
#define RECT

#include "libs.h"

typedef struct
{
    char text[20];
    GLuint textureID;
    float fontSize;
    int w;
    int h;
    bool centered;
} GLF_Text;

typedef struct
{
    float x, y;
    float w, h;
    float angle;
    GLF_Text text[1];
    GLuint textureID;   // Optional texture to be rendered, if both texture and text is present then text goes on top
    float tx, ty, tw, th; // Texture mapping values (max by default)
    uint8_t colour[3];
    uint32_t* data;

} GLF_Rect;

typedef struct
{
    float x, y;
    float w, h;
    float value;
} GLF_Slider;

GLF_Rect* GLF_CreateRect(float x, float y, float w, float h);

GLF_Slider* GLF_CreateSlider(float x, float y, float w, float h);

void GLF_CreateText(GLF_Rect* rect, char* str, bool centered);





#endif
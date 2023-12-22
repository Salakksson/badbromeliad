#include "rect.h"


GLF_Rect* GLF_CreateRect(float x, float y, float w, float h)
{
    GLF_Rect* rect = malloc(sizeof(GLF_Rect));
    
    rect->x = x, rect->y = y, rect->w = w, rect->h = h;
    rect->textureID = 0;
    rect->tx = 0, rect->ty = 0, rect->tw = 1, rect->th = 1;
    rect->colour[0] = 255;
    rect->colour[1] = 0;
    rect->colour[2] = 255;
    rect->text->fontSize = 0.08;
    rect->text->text = NULL;
    rect->text->textureID = 0;
    rect->angle = 0;
    return rect;
}

GLF_Slider* GLF_CreateSlider(float x, float y, float w, float h)
{
    GLF_Slider* slider = calloc(1, sizeof(GLF_Rect));
    
    slider->x = x, slider->y = y, slider->w = w, slider->h = h;

    return slider;
}

void GLF_CreateText(GLF_Rect* rect, char* str, bool centered)
{
    if (rect->text->textureID) 
    {
        glDeleteTextures(1, &rect->text->textureID);
    }
    rect->text->text = str;
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, str, textColor);
    
    GLuint textTexture;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textTexture);
    glBindTexture(GL_TEXTURE_2D, textTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    if (!strcmp(str, "1-5: Weapons"))
    {
        textSurface->w--;
    }
    if (!strcmp(str, "F11: Fullscreen (can crash)"))
    {
        textSurface->w+=2;
    }

    int len = (float)strlen(str);
    rect->text->w = textSurface->w * (len+1)/len;
    rect->text->h = textSurface->h;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->text->w, rect->text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textSurface->pixels);
    glDisable(GL_TEXTURE_2D);

    SDL_FreeSurface(textSurface);

    rect->text->textureID = textTexture;
    rect->text->centered = centered;
}

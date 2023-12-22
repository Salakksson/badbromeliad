#include "rendering.h"

bool* B_FPS;
bool* B_MENU;


void Render_DrawText(GLF_Text* text)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, text->textureID);

    float aspectRatio = (float)text->w / text->h;
    float height = text->fontSize;
    float width = aspectRatio * height / ASPECT_RATIO;
    
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(0, 0);
    glTexCoord2f(1, 1); glVertex2f(width, 0);
    glTexCoord2f(1, 0); glVertex2f(width, height);
    glTexCoord2f(0, 0); glVertex2f(0, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    
    
}

void Render_DrawTextC(GLF_Text* text)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, text->textureID);

    float aspectRatio = (float)text->w / text->h;
    float height = text->fontSize;
    float width = aspectRatio * height / ASPECT_RATIO;
    
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(-width/2, -height/2);
    glTexCoord2f(1, 1); glVertex2f(width/2, -height/2);
    glTexCoord2f(1, 0); glVertex2f(width/2, height/2);
    glTexCoord2f(0, 0); glVertex2f(-width/2, height/2);
    glEnd();


    glDisable(GL_TEXTURE_2D);

    
    
}

void GLF_DrawRect(GLF_Rect* rect)
{
    glLoadIdentity();
    glTranslatef(rect->x, rect->y, 0.0f);
    
    if (rect->text->text) 
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        
        if (rect->text->centered)
            Render_DrawTextC(rect->text);
        else
            Render_DrawText(rect->text);
        

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }

    if (rect->textureID) 
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, rect->textureID);

        glPushMatrix();

        if (rect->angle != 0)
        {
            glTranslatef(rect->w / 2, rect->h / 2, 0);
            glScalef(1, ASPECT_RATIO, 1);
            glRotatef(rect->angle, 0, 0, 1);
            glScalef(1, 1/ASPECT_RATIO, 1);
            glTranslatef(-rect->w / 2, -rect->h / 2, 0);
        }

        glBegin(GL_QUADS);
        glTexCoord2f(rect->tx, rect->ty); glVertex2f(0, 0);
        glTexCoord2f(rect->tx + rect->tw, rect->ty); glVertex2f(rect->w, 0);
        glTexCoord2f(rect->tx + rect->tw, rect->ty + rect->th); glVertex2f(rect->w, rect->h);
        glTexCoord2f(rect->tx, rect->ty + rect->th); glVertex2f(0, rect->h);
        glEnd(); 

        glPopMatrix();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glLoadIdentity();
        glColor3f(rect->colour[0]/255, rect->colour[1]/255, rect->colour[2]/255);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(rect->w, 0.0f);
        glVertex2f(rect->w, rect->h);
        glVertex2f(0.0f, rect->h);
        glEnd();
    }
    
}

void drawSlider(GLF_Slider* slider) 
{
    glLoadIdentity();
    
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(slider->x-slider->w/2, slider->y-slider->h/2);
    glVertex2f(slider->x+slider->w/2, slider->y-slider->h/2);
    glVertex2f(slider->x+slider->w/2, slider->y+slider->h/2);
    glVertex2f(slider->x-slider->w/2, slider->y+slider->h/2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    float handleWidth = slider->w * slider->value;
    glVertex2f(slider->x-slider->w/2,             slider->y-slider->h/2);
    glVertex2f(slider->x-slider->w/2+handleWidth, slider->y-slider->h/2);
    glVertex2f(slider->x-slider->w/2+handleWidth, slider->y+slider->h/2);
    glVertex2f(slider->x-slider->w/2,             slider->y+slider->h/2);
    glEnd();
}

void Render_ScreenDraw(SET* objs)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    GLF_DrawRect(objs->BG);

    // Transparent objects
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GameObj* obj = objs->player;
    while(obj)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        GLF_DrawRect(obj->model);
        obj = obj->next;
    }
    obj = objs->enemies->next;
    while(obj)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        GLF_DrawRect(obj->model);
        obj = obj->next;
    }
    if(*B_MENU)
    {   

        glColor3f(1.0f, 1.0f, 1.0f);
        GLF_DrawRect(objs->GuiBox);

        drawSlider(objs->slider);

        for (int i = 0; i < objs->menuTextCount; i++)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            GLF_DrawRect(objs->text[i]);
        }

        
        
        
    }
    if(*B_FPS)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        GLF_DrawRect(objs->FPS);
    }
    for (int i = 0; i < 3; i++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        GLF_DrawRect(objs->hearts[i]);
    }
    

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

    // glBegin(GL_QUADS);
    // glColor3f(1, 0, 0); glVertex2f(-1, -1);
    // glColor3f(0, 1, 0); glVertex2f(-1, 1);
    // glColor3f(0, 0, 1); glVertex2f(1 , 1);
    // glColor3f(0, 1, 1); glVertex2f(1, -1);
    // glEnd();

    
}


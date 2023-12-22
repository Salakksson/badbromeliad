#include "GUI.h"

// typedef struct
// {
//     GLF_Rect* BG;


    
//     GameObj* player;

//     GLF_Rect* GuiBox;

//     GLF_Rect* FPS;

// } SET;

void InitGui(SET* objs)
{   
    GLuint Texture_Enemy = SOIL_load_OGL_texture(ASSETS_DIRECTORY "enemy.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint Texture_Ananas = SOIL_load_OGL_texture(ASSETS_DIRECTORY "ananas.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint Texture_AnanasBase = SOIL_load_OGL_texture(ASSETS_DIRECTORY "base.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint Texture_AnanasStem = SOIL_load_OGL_texture(ASSETS_DIRECTORY "stem.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLuint Texture_BG = SOIL_load_OGL_texture(ASSETS_DIRECTORY "bg.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint Texture_Menu = SOIL_load_OGL_texture(ASSETS_DIRECTORY "menu-1x1.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint Texture_Heart = SOIL_load_OGL_texture(ASSETS_DIRECTORY "heart.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint Texture_bHeart = SOIL_load_OGL_texture(ASSETS_DIRECTORY "bheart.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    objs->BG = GLF_CreateRect(-1, -1, 2, 2 * ASPECT_RATIO);
	objs->BG->textureID = Texture_BG;

    objs->hearts[0] = GLF_CreateRect(0.7, 1-0.1*ASPECT_RATIO , 0.1, 0.1 * ASPECT_RATIO);
	objs->hearts[0]->textureID = Texture_Heart;
    objs->hearts[1] = GLF_CreateRect(0.8, 1-0.1*ASPECT_RATIO , 0.1, 0.1 * ASPECT_RATIO);
	objs->hearts[1]->textureID = Texture_bHeart;
    objs->hearts[2] = GLF_CreateRect(0.9, 1-0.1*ASPECT_RATIO , 0.1, 0.1 * ASPECT_RATIO);
	objs->hearts[2]->textureID = Texture_bHeart;

    objs->player = createObj(-(PLAYER_SIZE / ASPECT_RATIO) /2, -PLAYER_SIZE/2, PLAYER_SIZE / ASPECT_RATIO, PLAYER_SIZE, Texture_Ananas, NULL);
    objs->player->model->angle = 0;
    objs->player->model->data = (uint32_t*)calloc(5, sizeof(uint32_t));
    objs->player->next = NULL;

    objs->enemies = createObj(0, 0, 0, 0, 1, NULL);
    objs->player->model->angle = 0;
    objs->player->next = NULL;

    objs->GuiBox = GLF_CreateRect(-0.5, -0.5*ASPECT_RATIO, 1, ASPECT_RATIO);
    objs->GuiBox->textureID = Texture_Menu;
	//objs->GuiBox->text = "GUI";
    
    objs->text = malloc(sizeof(objs->text) * 20);
    float o_text_pos = objs->GuiBox->y + (objs->GuiBox->h * 0.8);
    float text_pos = o_text_pos;
    objs->menuTextCount = 0;

    // Top of menu
    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "Game Paused", true);
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize * 2;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "Controls:", true);
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;\
    GLF_CreateText(objs->text[objs->menuTextCount], "WASD: Movement", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "Mouse: Attack", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "1-5: Weapons", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "ESC: Pause/Menu", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "F1: FPS counter", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "F4: Close game", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "F11: Fullscreen", true);
    objs->text[objs->menuTextCount]->text->fontSize = 0.06;
    text_pos -= objs->text[objs->menuTextCount]->text->fontSize*2;
    objs->menuTextCount++;

    objs->text[objs->menuTextCount] = GLF_CreateRect(0, 0, 0, 0);
	objs->text[objs->menuTextCount]->y = text_pos;
    GLF_CreateText(objs->text[objs->menuTextCount], "Music volume:", true);

    text_pos -= objs->text[objs->menuTextCount]->text->fontSize * 1.5;
    objs->menuTextCount++;

    objs->slider = GLF_CreateSlider(0, 0, 0.4, 0.1);
	objs->slider->y = text_pos;
    objs->slider->value = 0.5;
    

    objs->FPS = GLF_CreateRect(-1, 0, 0, 0);
	objs->FPS->y = 1 - objs->FPS->text->fontSize;
    GLF_CreateText(objs->FPS, malloc(10), false);
    objs->FPS->data = (uint32_t*)calloc(1, 1);
}
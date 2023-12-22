#include "gameobj.h"



GameObj* createObj(float x, float y, float w, float h, GLuint textureID, GameObj* prev)
{
    GameObj* obj = (GameObj*)malloc(sizeof(GameObj));
    obj->model = GLF_CreateRect(x, y, w, h);
    obj->dx = 0, obj->dy = 0;
    obj->model->textureID = textureID;
    obj->prev = prev;
    if (prev)
        prev->next = obj;
    obj->next = NULL;
    return obj;
}

/*
This function does not automatically set the value to Null
This may be unsafe when using multiple threads or accessing linked lists
*/
void freeObj(GameObj* obj)
{
    SDL_LockMutex(listMutex);

    if (obj->prev)
    obj->prev->next = obj->next;
    if (obj->next)
        obj->next->prev = obj->prev;
    free(obj);
    
    SDL_UnlockMutex(listMutex); 
}
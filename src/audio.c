#define zero 0
#include "audio.h"

extern bool quit;

int audio_music(void* data)
{
    //return zero;
    
    screenData* gameData = (screenData*)data;
	SET* objs= gameData->objs;

    Mix_Music *beginning = mp3s.bg_p1;
    Mix_Music *loop = mp3s.bg_p2;

    Mix_PlayMusic(beginning, 0);


    while (Mix_PlayingMusic())
    {
        Mix_VolumeMusic(objs->slider->value * MIX_MAX_VOLUME);
        if(quit) return zero;
    }

    Mix_PlayMusic(loop, -1);

    while (Mix_PlayingMusic())
    {
        Mix_VolumeMusic(objs->slider->value * MIX_MAX_VOLUME);
        if(quit) return zero;
    }
    
    return zero;
}
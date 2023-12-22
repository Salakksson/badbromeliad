#define zero 0
#include "audio.h"

extern bool quit;

int audio_music(void* data)
{
    //return zero;
    
    screenData* gameData = (screenData*)data;
	SET* objs= gameData->objs;

    // MPG123 initialisation
    bool mpgerr = false;
    mpg123_init();
    mpg123_handle *mh = mpg123_new(NULL, NULL);
    if (mh == NULL) 
        mpgerr = true;
    if (mpg123_open(mh, ASSETS_DIRECTORY "bg_p1.mp3") != MPG123_OK)
        mpgerr = true;
    
    long rate;
    mpg123_scan(mh);
    mpg123_getformat(mh, &rate, NULL, NULL);
    off_t length = mpg123_length(mh) * 1000 / rate;
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    // SDL Mixer
    Mix_Music *beginning = mp3s.bg_p1;
    Mix_Music *loop = mp3s.bg_p2;

    // clock_t start = clock();                                                //  Finding how long it takes for SDL to start playing song
    Mix_PlayMusic(beginning, 0);                                               //  This is done to make waiting for part1 to finish more accurate
    // clock_t end = clock();                                                  //  This then makes a smooth transition from the intro of the song to the looping part
    // off_t magicNum = 1000 * ((double) (end - start)) / CLOCKS_PER_SEC;      //  This line could be made more efficient

    // if (!mpgerr)
    // {
    //     //printf("%ld, %ld, %ld, %ld\n", length, magicNum, start, end);
    //     SDL_Delay(length);
    // }
    //else
    {
        while (Mix_PlayingMusic())
        {
            Mix_VolumeMusic(objs->slider->value * MIX_MAX_VOLUME);
            if(quit) return zero;
        }
    }
    Mix_PlayMusic(loop, -1);

    while (Mix_PlayingMusic())
    {
        Mix_VolumeMusic(objs->slider->value * MIX_MAX_VOLUME);
        if(quit) return zero;
    }
    
    return zero;
}
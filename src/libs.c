#include "libs.h"

float ASPECT_RATIO;

SDL_Window* window;
TTF_Font* font;
SDL_Color textColor;
SDL_GLContext GL;

SDL_mutex* listMutex;

// Textures
// extern GLuint Texture_Ananas;
// extern GLuint Texture_BG;

bool inRangef(float low, float high, float x)          
{          
 return (low <= x && x <= high);          
} 

musicPlayer mp3s;

int InitSDL(char* name, int x, int y, bool fs)
{
	// Initialise video
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Init Error", SDL_GetError(), NULL);
		return -1;
	}

	window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Window Error", SDL_GetError(), NULL);
		return -2;
	}
	if (fs)
	{
		if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fullscreen Error", SDL_GetError(), NULL);
			return -3;
		}
	}

	// Initialise audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) 
	{
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", SDL_GetError(), NULL);
		return -4;
    }

	mp3s.bg_p1 = Mix_LoadMUS(ASSETS_DIRECTORY "bg_p1.mp3");
    if (!mp3s.bg_p1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer load Error", SDL_GetError(), NULL);
        Mix_CloseAudio();
        return -5;
    }

	mp3s.bg_p2 = Mix_LoadMUS(ASSETS_DIRECTORY "bg_p2.mp3");
    if (!mp3s.bg_p2) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer load Error", SDL_GetError(), NULL);
        Mix_CloseAudio();
        return -5;
    }

	if (TTF_Init() == -1) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Init Error", SDL_GetError(), NULL);
        return false;
    }

    // Load a TrueType font
    font = TTF_OpenFont(ASSETS_DIRECTORY "font.ttf", 28);
    if (!font) 
	{
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Open Error", SDL_GetError(), NULL);
        return false;
    }

	SDL_mutex* listMutex = SDL_CreateMutex();

	textColor.r = 255, textColor.g = 255, textColor.b = 255, textColor.a = 255;
	return 0;

}

void InitGL()
{
	GL = SDL_GL_CreateContext(window);

	if (!GL) 
	{
    fprintf(stderr, "Error creating OpenGL context: %s\n", SDL_GetError());
    // Handle error appropriately (e.g., exit the program)
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetSwapInterval(0);
	

	int x, y;
	SDL_GetWindowSize(window, &x, &y);
	ASPECT_RATIO = (float)x/(float)y;
	glViewport(0, 0, x, y);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
    //glOrtho(0, x, y, 0, -1, 1);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.2f, 0.0f, 0.5f, 1.0f);
	
}

void Cleanup()
{
    Mix_FreeMusic(mp3s.bg_p2);
    Mix_CloseAudio();

	TTF_CloseFont(font);
    TTF_Quit();

    SDL_GL_DeleteContext(GL);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

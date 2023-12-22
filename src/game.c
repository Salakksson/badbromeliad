#include "game.h"


bool quit;
bool INIT = false;

int msPerSpawn(int round)//, float updateTime)
{
	double spawnTime = 3000/(round*log10(round)+2);
	//int frames = (int)(spawnTime/updateTime);
	//return frames;
	return (int)spawnTime;
}

float q_rsqrt(float number)
{
	return 1/sqrt(number);
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

int game_main(void* data)
{
	screenData* gameData = (screenData*)data;
	SET* objs= gameData->objs;
	
	for(;!INIT;);			// Best line of code ever written
	/*
		This line stalls the cpu untill INIT is set to true (after the ui struct is initialised in the rendering thread)
		This saves extra checks later in the loop and slightly increases performance
		This is also just a beautiful line of code in its own right

		This is done to prevent a segfault when moving the character
	*/

	clock_t current = clock(); 
	clock_t prev = current; 
	clock_t lastSpawnClock = current; 
	int round = 1;

	GameObj* firstObj = objs->enemies;
	GameObj* lastObj = firstObj;


	float UpdateTime = 1000/60;

	bool* input = (bool*)calloc(1, 256);
	bool mouse1 = false;
	// Inputs
    while (!quit)
    {	
		event:
        SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				input[e.key.keysym.scancode] = true;

				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					*B_MENU = !*B_MENU;
					break;
				case SDLK_F1:
					*B_FPS = !*B_FPS;
					break;
				case SDLK_F4:
					quit = true;
					break;
				case SDLK_F11:
					gameData->fs = !gameData->fs;
					
					if (gameData->fs)
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
					else
						SDL_SetWindowFullscreen(window, 0);

					gameData->reload = true;
					break;
				}
				break;
			case SDL_KEYUP:
				input[e.key.keysym.scancode] = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
				{	
					mouse1 = true;
					int mx, my;
					SDL_GetMouseState(&mx, &my);
					int ww, wh;
					SDL_GetWindowSize(window, &ww, &wh);
					float mxf = ((float)mx/(float)ww)*2 - 1;
					float myf = -((float)my/(float)wh)*2 +1;
					bool onBoxX = inRangef(objs->slider->x - objs->slider->w/2, objs->slider->x + objs->slider->w/2, mxf);
					bool onBoxY = inRangef(objs->slider->y - objs->slider->h/2, objs->slider->y + objs->slider->h/2, myf);
					if (onBoxX && onBoxY)
					{
						objs->slider->value = (mxf - objs->slider->x + objs->slider->w/2) / (objs->slider->w);
					}
					if (!(objs->player->model->data[0] || *B_MENU))
					{
						objs->player->model->textureID++;
						objs->player->model->data[0] = 2*RELOAD_TIME / UpdateTime;

						
						GameObj* scan_lastobj = NULL;
						GameObj* scan_obj = objs->player;
						while(scan_obj)
						{
							scan_lastobj = scan_obj;
							scan_obj = scan_obj->next;
						}
						scan_obj = createObj(objs->player->model->x, objs->player->model->y, objs->player->model->w, objs->player->model->h, objs->player->model->textureID+1, scan_lastobj);
						scan_obj->model->angle = objs->player->model->angle;
						scan_obj->dx = cos((objs->player->model->angle + 90) * PI / 180)/100;
						scan_obj->dy = sin((objs->player->model->angle + 90) * PI / 180)/100;

						objs->player->dx -= scan_obj->dx;
						objs->player->dy -= scan_obj->dy;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT)
				{	
					mouse1 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				if (mouse1)
				{
					int mx, my;
					SDL_GetMouseState(&mx, &my);
					int ww, wh;
					SDL_GetWindowSize(window, &ww, &wh);
					float mxf = ((float)mx/(float)ww)*2 - 1;
					float myf = -((float)my/(float)wh)*2 +1;
					bool onBoxX = inRangef(objs->slider->x - objs->slider->w/2, objs->slider->x + objs->slider->w/2, mxf);
					bool onBoxY = inRangef(objs->slider->y - objs->slider->h/2, objs->slider->y + objs->slider->h/2, myf);
					if (onBoxX && onBoxY)
					{
						objs->slider->value = (mxf - objs->slider->x + objs->slider->w/2) / (objs->slider->w);
					}
				}
				break;
			}
	 	}

		/// Rest of game loop





		// Game movement
		current = clock(); 

		clock_t ms = 1000.0f * (float)(current - prev) / (float)CLOCKS_PER_SEC;
		clock_t lastSpawn = 1000.0f * (float)(current - lastSpawnClock) / (float)CLOCKS_PER_SEC;

		float enemySpeed = 1.0f / 200.0f;

		if (lastSpawn / 2>= msPerSpawn(round))
		{
			//printf("%d\n", msPerSpawn(round));
			lastSpawnClock = current;
			if (*B_MENU)
				goto event;	// pause

			

			GameObj* obj;
			for (obj = objs->enemies; obj->next != NULL; obj = obj->next);
			//printf("making enemy: %p, %p\n", obj, obj->next);
			int iX = rand()%2;
			float eX;
			float eY;
			if (iX)
			{
				eX = -1.5 + ((float)rand() / RAND_MAX) * 3;
				eY = rand()%2 * 4 - 2;
			}
			else
			{
				eY = -1.5 + ((float)rand() / RAND_MAX) * 3;
				eX = rand()%2 * 4 - 2;
			}
			obj->next = createObj(eX, eY, PLAYER_SIZE / ASPECT_RATIO, PLAYER_SIZE, 1, obj);

			float oex = (obj->next->model->x + obj->next->model->w/2);
			float oey = (obj->next->model->y + obj->next->model->h/2);
			float dx = (objs->player->model->x + objs->player->model->w/2 - oex);
			float dy = (objs->player->model->y + objs->player->model->h/2 - oey);
			float normal = q_rsqrt(dx * dx + dy * dy);
			obj->next->dx = dx * enemySpeed * normal * ASPECT_RATIO;
			obj->next->dy = dy * enemySpeed * normal;
			


		}
		if (ms >= UpdateTime)	// Constantly timed calls
		{
			srand(current);
			prev = current; 
			if (*B_MENU)
				goto event;	// pause
			

			if(input[SDL_SCANCODE_W])
				objs->player->dy = fminf(objs->player->dy + PLAYER_ACCEL, PLAYER_MAXSPEED);
			if(input[SDL_SCANCODE_A])
				objs->player->dx = fmaxf(objs->player->dx - PLAYER_ACCEL, -PLAYER_MAXSPEED);
			if(input[SDL_SCANCODE_S])
				objs->player->dy = fmaxf(objs->player->dy - PLAYER_ACCEL, -PLAYER_MAXSPEED);
			if(input[SDL_SCANCODE_D])
				objs->player->dx = fminf(objs->player->dx + PLAYER_ACCEL, PLAYER_MAXSPEED);

			GameObj* obj = objs->player;
			while(obj)
			{
				obj->model->x += obj->dx / ASPECT_RATIO;
				obj->model->y += obj->dy;
				GameObj* next = obj->next;
				if (!inRangef(-1.3, 1.3, obj->model->x) || !inRangef(-1.3, 1.3, obj->model->y))
				{
					freeObj(obj); 
					obj = NULL;
				}
				obj = next;
			}
			
			obj = objs->enemies->next;
			while(obj)
			{
				obj->model->x += obj->dx / ASPECT_RATIO;
				obj->model->y += obj->dy;
				GameObj* next = obj->next;
				float oex = (obj->model->x + obj->model->w/2);
				float oey = (obj->model->y + obj->model->h/2);
				float dx = (objs->player->model->x + objs->player->model->w/2 - oex);
				float dy = (objs->player->model->y + objs->player->model->h/2 - oey);
				float normal = q_rsqrt(dx * dx + dy * dy);
				
				obj->dx = dx * enemySpeed * normal * ASPECT_RATIO;
				obj->dy = dy * enemySpeed * normal;
				if (!inRangef(-3, 3, obj->model->x) || !inRangef(-3, 3, obj->model->y))
				{
					freeObj(obj); 
					obj = NULL;
				}
				GameObj* bullet = objs->player->next;
				while(bullet)
				{
					GameObj* next = bullet->next;

					if (inRangef(bullet->model->x, bullet->model->x + bullet->model->w, obj->model->x + obj->model->w/2) && inRangef(bullet->model->y, bullet->model->y + bullet->model->h, obj->model->y + obj->model->h/2))
					{
						freeObj(obj); 
						obj = NULL;
						freeObj(bullet); 
						bullet = NULL;
					}
					bullet = next;
				}
				obj = next;
			}

			objs->player->dx *= FRICTION;
			objs->player->dy *= FRICTION;

			if(objs->player->model->x + objs->player->model->w  > 1)
			{
				objs->player->model->x = 1 - objs->player->model->w;
				objs->player->dx = 0;
			}	
			if(objs->player->model->x < -1)
			{
				objs->player->model->x = -1;
				objs->player->dx = 0;
			}

			if(objs->player->model->y + objs->player->model->h > 1)
			{
				objs->player->model->y = 1 - objs->player->model->h;
				objs->player->dy = 0;
			}	
			if(objs->player->model->y < -1)
			{
				objs->player->model->y = -1;
				objs->player->dy = 0;
			}

			int mx;
			int my;
			SDL_GetMouseState(&mx, &my);
			int ww;
			int wh;
			SDL_GetWindowSize(window, &ww, &wh);

			float px = ww * (objs->player->model->x + objs->player->model->w/2 + 1.0) / 2.0;
			float py = wh - wh * (objs->player->model->y + objs->player->model->h/2 + 1.0) / 2.0;
			float dx = px - mx;
			float dy = py - my;

			
			objs->player->model->angle =  90 - atan2(dy, dx) * 180/PI;


			if(objs->player->model->data[0])
			{
				objs->player->model->data[0]--;

				if(!objs->player->model->data[0])
				{
					objs->player->model->textureID--;
				}
			}
		}
		




    }
    return 0;
}

int game_rendering(void* data)
{
	screenData* gameData = (screenData*)data;
	SET* objs = gameData->objs;

	InitGL();

	B_FPS = calloc(1, 1);

	B_MENU = calloc(1, 1);
	*B_MENU = true;


	InitGui(objs);

	INIT = true; false;
	
	int frames = 0;
	clock_t prev = clock(); 
    clock_t current = clock(); 
    while (!quit)
	{
		if (gameData->reload)
		{
			SDL_LockMutex(listMutex);

			SDL_GL_DeleteContext(GL);
			InitGL();

			GameObj* savell = objs->player->next;
			InitGui(objs);
			objs->player->next = savell;
			objs->player->next->prev = objs->player;
			gameData->reload = false;

			SDL_UnlockMutex(listMutex);
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{	// I wrote a scope here for some reason, ill just keep it here because why not!

			Render_ScreenDraw(objs);

		}
		SDL_GL_SwapWindow(window);			// Swap buffers

		current = clock(); 
		frames++;
		if ((current - prev) / CLOCKS_PER_SEC)
		{
			prev = current;
			sprintf(objs->FPS->text->text, "FPS: %d", frames);
			GLF_CreateText(objs->FPS, objs->FPS->text->text, false);
			frames = 0;
		}
		
    }

	// Free booleans
    return 0;
}
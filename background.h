#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include"SDL.h"
#include"p1.h"
#include"p2.h"

class background{
	SDL_Surface *b,*life,*energe,*life1,*life2,*vs;
	SDL_Rect clip[4],pos[8];
public:
	background();
	void draw(man c1,man c2);
};

#endif

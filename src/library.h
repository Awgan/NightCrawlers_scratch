#ifndef LIBRARY_H_
#define LIBRARY_H_

#define PI 3.1415

#include <iostream>
#include <SDL2/SDL.h>

enum dirc {left, center, right};
enum team {red=0, green};

const int MOVE_SPEED = 5;
const int MOVE_L = MOVE_SPEED * (-1);
const int MOVE_R = MOVE_SPEED * (1);
const int MOVE_U = MOVE_SPEED * (-1);
const int MOVE_D = MOVE_SPEED * (1);

const int GRAVITY = 2;

const int BULLET_SPEED = 17;
const int ROTATE = 6;
const int HERO_SCALE = 8;

#define SPRITE_NUMBERS 10

const char * const SPRITES[SPRITE_NUMBERS] = {
	"../fig/sw02.bmp",		//hero sprite
	"../fig/guns03.bmp",	//effects sprite > bullet
	"../fig/bground.bmp",	//background
	"../fig/guns03.bmp",
	"../fig/sw02_red.bmp",
	"../fig/sw02_green.bmp",
	"../fig/wall01.bmp"	
};

#define BACKGROUND SPRITES[2]

const SDL_Rect heroSprite[2][3] = {
	{{0,0,154,292},{160,303,152,295},{360,597,150,296}},
	{{870,0,154,292},{712,303,152,295},{514,598,150,296}}	
};

const SDL_Rect bulletSprite[1] = {
	20,178,6,6
};

const SDL_Rect targetSprite[1] = {
	230,2,32,31
};

const SDL_Rect wallSprite[1] = {
	11,21,616,53
};

inline void tex_make( SDL_Renderer * _rend, SDL_Texture * _tex, unsigned char _spr = 0 ) {
	
	SDL_Surface * surf = SDL_LoadBMP( SPRITES[ _spr ] ); 
	Uint32 colorkey = SDL_MapRGB( surf->format, 255, 0, 255 );
	SDL_SetColorKey( surf, SDL_TRUE, colorkey );	
	
	_tex = SDL_CreateTextureFromSurface( _rend, surf );
	
	SDL_FreeSurface( surf );
	
}

#endif

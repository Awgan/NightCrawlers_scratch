
#include <iostream>
#include <cstring>
#include <math.h>


#include "target.h"

#define PI 3.1415

void licz() {
	static int jpk = 0;
	jpk++;
	//std::cout << "Target: " << jpk << std::endl;
}

Target::Target() {
//std::cout << "Target()\n";
int len = std::strlen(SPRITES[3]);
	sprite = new char [ len + 1];
	std::strcpy(sprite, SPRITES[3]);

}

Target::Target(SDL_Renderer * _rend, int * _cX, int * _cY, dirc _d) {
std::cout << "Target(render)\n";
	visible = false;
	rend = _rend;

	
	target.dist = 45;
	target.d = _d;	
	target.angle = (target.d == left ? 180 : 0);	//degre; max 360

	target.x = *_cX + target.dist * cos(target.angle * PI / 180) + heroSprite[0][0].w/(HERO_SCALE * 2) - targetSprite[0].w/(2 * 2);
	target.y = *_cY + target.dist * sin(target.angle * PI / 180) + heroSprite[0][0].h/(HERO_SCALE * 2) - targetSprite[0].h/(2 * 2);

	target.x_cen = _cX;
	target.y_cen = _cY;

	int len = std::strlen(SPRITES[3]);
	sprite = new char [ len + 1];
	std::strcpy(sprite, SPRITES[3]);
	
	/*SDL_Surface * surf = SDL_LoadBMP(sprite);
	Uint32 colorkey = SDL_MapRGB(surf->format,255,0,255);
	SDL_SetColorKey(surf,SDL_TRUE,colorkey);	
	tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface( surf );*/
	
	tex_make( rend, tex, 3 );

}

Target::~Target(){
//std::cout << "~Target()\n";
licz();
	delete sprite;
	}

Target::Target( const Target & _t ) {
std::cout << "Target(Target)\n";
	visible = _t.visible;
	rend = _t.rend;
	
	target.angle = _t.target.angle;	//degre; max 360
	target.dist = _t.target.dist;
	target.x = _t.target.x;
	target.y = _t.target.y;
	
	target.x_cen = _t.target.x_cen;
	target.y_cen = _t.target.y_cen;
	
	target.d = _t.target.d;
	
	int len = std::strlen(_t.sprite);

	sprite = new char [ len + 1];
	std::strcpy(sprite, _t.sprite);

	SDL_Surface * surf = SDL_LoadBMP(sprite);
	Uint32 colorkey = SDL_MapRGB(surf->format,255,0,255);
	SDL_SetColorKey(surf,SDL_TRUE,colorkey);	
	tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface( surf );
}

void Target::xy_calc() {
//licz();	
static int pomx = heroSprite[0][0].w/(HERO_SCALE * 2) - targetSprite[0].w/(2 * 2);
static int pomy = heroSprite[0][0].h/(HERO_SCALE * 2) - targetSprite[0].h/(2 * 2);
		
		target.x = *target.x_cen + target.dist * cos(target.angle * PI / 180) + pomx; 
		target.y = *target.y_cen + target.dist * sin(target.angle * PI / 180) + pomy; 
						
	
		//std::cout << "target.angle: " << target.angle << '\n';
		//std::cout << "target.x: " << target.x << '\n';
		//std::cout << "target.y: " << target.y << '\n';
}

void Target::angle_calc() {
//std::cout << ( target.x - (*target.x_cen ) ) / target.dist << '\n';
	if ( target.angle >= 0 && target.angle < 90 ) {
		target.angle = 180 - target.angle;
	}
	else if ( target.angle >= 90 && target.angle < 180 ) {
		target.angle = 180 - target.angle;
	}
	else if ( target.angle >= 180 && target.angle < 270 ) {
		target.angle = 360 - (target.angle - 180);
	}
	else if ( target.angle >= 270 && target.angle < 360 ) {
		target.angle = 180 + ( 360 - target.angle );
	}
if ( target.angle == 360 )
		target.angle = 0;
//std::cout << "angle_calc: " << target.angle << '\n';
xy_calc();
}

void Target::moveX(int _mv) {

static dirc temp_dirc = left;
	if ( _mv != 0 ) {
		temp_dirc = target.d;
		
		target.d = _mv > 0 ? right : left;
		if (temp_dirc != target.d ) {
			if ( temp_dirc == left && target.angle > 90 && target.angle < 270 ) {
				target.x = *target.x_cen + heroSprite[0][0].h/(HERO_SCALE * 2) + ( (*target.x_cen + heroSprite[0][0].h/(HERO_SCALE * 2)) - target.x );
				angle_calc();
				
			} else if ( temp_dirc == right && ( target.angle < 90 || target.angle > 270 ) ) {
				target.x = *target.x_cen + heroSprite[0][0].h/(HERO_SCALE * 2) - ( target.x - (*target.x_cen + heroSprite[0][0].h/(HERO_SCALE * 2)) );
				angle_calc();
			}
		
		//std::cout << "target.x: " << target.x << std::endl;	
		
		}
		
		target.x += _mv;		
	}	
}

void Target::moveY(int _mv) {
 //14
	if ( _mv != 0 ) {
		target.y += _mv;
		
	}	
}

void Target::rotate(int _deg) {
//std::cout << "Rotate()\n";
visible = true;
	if ( _deg != 0 ) {
		if ( _deg > 360 || _deg < 0 ) {
			_deg = _deg % 360;
		}
			
		target.angle += ( target.d == left ? (1 * _deg) : (-1 * _deg) );	
		if ( target.angle < 0 )
			target.angle = target.angle + 360;
		else if ( target.angle >= 360 )
			target.angle = target.angle - 360;
			
		
		
		xy_calc();
	}
	
}

double Target::getangle() {
	return target.angle;
}

void Target::show() {

//std::cout << "show\n";
if ( visible == true ) {		
		SDL_Rect rect;
		rect.x = target.x;
		rect.y = target.y;
		rect.w = targetSprite[0].w / (2);
		rect.h = targetSprite[0].h / (2);
	
		SDL_RenderCopy(rend, tex, &targetSprite[0], &rect);			
	}		
}


Target & Target::operator=(const Target & _t ) {
std::cout << "operator=\n";

	if ( this == &_t )
		return *this;
	visible = _t.visible;
	rend = _t.rend;
	
	target.angle = _t.target.angle;	//degre; max 360
	target.dist = _t.target.dist;
	target.x = _t.target.x;
	target.y = _t.target.y;
	
	target.x_cen = _t.target.x_cen;
	target.y_cen = _t.target.y_cen;
	
	target.d = _t.target.d;
	
	int len = std::strlen(_t.sprite);
	delete sprite;
	sprite = new char [ len + 1];
	std::strcpy(sprite, _t.sprite);
		
	SDL_Surface * surf = SDL_LoadBMP(sprite);
	Uint32 colorkey = SDL_MapRGB(surf->format,255,0,255);
	SDL_SetColorKey(surf,SDL_TRUE,colorkey);	
	tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface( surf );
	
	return *this;
	
}


#include <cstring>
#include <iostream>

#include <SDL2/SDL.h>

#include "bullet.h"
#include "collision.h"

void ccount() {
	static int c = 1;
	std::cout << "Pozycja: bullet: "<< c << std::endl;
	c++;
}

Bullet::Bullet() : Position () , coll(& strcoll) {
	//std::cout << "BULLET: konstruktor domyslny\n";
	
	rend = NULL;
	tex = NULL;
	
	sprite = NULL;	
	speed = 0;
	angle = 0;	
	visible = true;
	typ = Collision::collType::bullet;	
	
	strcoll.x = Position::getXp();
	strcoll.y = Position::getYp();
	strcoll.w = &destRect.w;
	strcoll.h = &destRect.h;
	strcoll.typ = &typ;
	
}

Bullet::~Bullet() {
	//std::cout << "BULLET: destruktor!\n";
	delete [] sprite;
	
	SDL_DestroyTexture( tex );
}

Bullet::Bullet(SDL_Renderer * _rend, const sPosition _pos, const double & _ang) : Position(_pos), coll(& strcoll) {
	
		
	rend = _rend;
	
	int len = std::strlen(SPRITES[1]);
	sprite = new char[len + 1];
	std::strcpy(sprite, SPRITES[1]);
	
	speed = BULLET_SPEED;
	angle = _ang;	
	visible = true;
	typ = Collision::collType::bullet;
	
	SDL_Surface * surf = SDL_LoadBMP(sprite);
	
	Uint32 colorkey = SDL_MapRGB(surf->format,255,0,255);

	SDL_SetColorKey(surf,SDL_TRUE,colorkey);
	
	tex = SDL_CreateTextureFromSurface(rend, surf);
	
	SDL_FreeSurface( surf );
	
	strcoll.x = Position::getXp();
	strcoll.y = Position::getYp();
	strcoll.w = &destRect.w;
	strcoll.h = &destRect.h;
	strcoll.typ = &typ;

}
		
void Bullet::moveAuto() {
	
	if ( speed != 0  && visible == true) 
	{
		Position::setAngle(angle);
		if (!Position::move( speed, angle) )
	
		//if ( getX() - BULLET_SPEED <= 0 || getLimX() <= getX() + BULLET_SPEED)
			visible = false;	
	}
}

void Bullet::show() {
	
	
		destRect.x = Position::getX();
		destRect.y = Position::getY();
		destRect.w = bulletSprite[0].w;
		destRect.h = bulletSprite[0].h;
	
	SDL_RenderCopy(rend, tex, &bulletSprite[0], &destRect);
	
	moveAuto();
	
}

Bullet & Bullet::operator=(const Bullet & _bull) {
	
	Position::operator =(_bull);
	
		
	rend = _bull.rend;	
	
	int len = std::strlen(_bull.sprite);
		
	delete [] sprite;
	
	sprite = new char[len + 1];
	
	std::strcpy(sprite, _bull.sprite);
	
	speed = _bull.speed;
	angle = _bull.angle;	
	visible = _bull.visible;
	typ = _bull.typ;
	
	SDL_Surface * surf = SDL_LoadBMP(sprite);
	tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface( surf);
	
	strcoll = _bull.strcoll;
	
	return *this;
	
}















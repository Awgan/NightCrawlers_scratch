
#include <cstring>
#include <iostream>

#include "hero.h"

void count() {
	static int c = 1;
	std::cout << "Pozycja: hero: "<< c << std::endl;
	c++;
}


Hero::Hero() : position(), coll(& strcoll) {
//std::cout << "Hero::Hero()\n";
		bulletNumber = 0;
		arrBullets = NULL;
		
		rend = NULL;
		tex = NULL;
		
		name = NULL;
		typ = Collision::collType::hero;
			
		sprite = NULL;
		
		actPosture = 0;
		
		speedX = 0;
		speedY = 0;
		angle = 0;
		health = 0;
		armor = 0;
		
		destRect = {0,0,0,0};
		
		strcoll.x = position.getXp();
		strcoll.y = position.getYp();
		strcoll.w = &destRect.w;
		strcoll.h = &destRect.h;
		strcoll.typ = &typ;
std::cout << *(strcoll.x) << '\n';			
		targ = Target(rend, strcoll.x, strcoll.y, position.getD());
}

Hero::~Hero() {
	delete [] name;
	delete [] sprite;
	delete [] arrBullets;
	
	SDL_DestroyTexture( tex );
	
}

Hero::Hero(SDL_Renderer * _rend, const char * _name, const sPosition & _pos, Platform * _plat) : position(_pos), coll(& strcoll) {
//std::cout << " Hero::Hero(SDL_Renderer * _rend, const char * _name, const sPosition & _pos)\n";
		
		bulletNumber = 0;
		arrBullets = NULL;
			
		rend = _rend;
		
		int len = std::strlen(_name);
		name = new char[len + 1];
		std::strcpy(name, _name);
				
		len = std::strlen(name[0] == 'r' ? SPRITES[4] : SPRITES[5]);	
		sprite = new char[len + 1];
		std::strcpy(sprite, name[0] == 'r' ? SPRITES[4] : SPRITES[5]);

		actPosture = 0;
		typ = Collision::collType::hero;
		speedX = 0;
		speedY = 0;
		angle = 0;
		health = 10;
		armor = 50;
		
		destRect = {0,0,0,0};
		
		strcoll.x = position.getXp();
		strcoll.y = position.getYp();
		strcoll.w = &destRect.w;
		strcoll.h = &destRect.h;
		strcoll.typ = &typ;

		SDL_Surface * surf = SDL_LoadBMP(sprite);

		Uint32 colorkey = SDL_MapRGB(surf->format,255,12,255);

		SDL_SetColorKey(surf,SDL_TRUE,colorkey);

		tex	= SDL_CreateTextureFromSurface(rend, surf);

		SDL_FreeSurface(surf);
		
		
		targ = Target(rend, strcoll.x, strcoll.y, position.getD());
		
		plat = _plat;
}

Hero::Hero(const Hero & _h) : position(_h.position), coll(& strcoll) {
	
//std::cout << 	"Hero::Hero(const Hero & _h)\n";
	bulletNumber = _h.bulletNumber;
	
	rend = _h.rend;
	
	
	int len = std::strlen(_h.name);
	name = new char[len + 1];
	std::strcpy(name, _h.name);
	
	len = std::strlen(_h.sprite);	
	sprite = new char[len + 1];
	std::strcpy(sprite, _h.sprite);
	
	SDL_Surface * surf = SDL_LoadBMP(sprite);

	Uint32 colorkey = SDL_MapRGB(surf->format,255,12,255);

	SDL_SetColorKey(surf,SDL_TRUE,colorkey);

	tex	= SDL_CreateTextureFromSurface(rend, surf);

	SDL_FreeSurface(surf);
	
	actPosture = _h.actPosture;
	
	speedX = _h.speedX;
	speedY = _h.speedY;
	angle = _h.angle;
	health = _h.health;
	armor = _h.armor;	
	typ = _h.typ;
	
		
	strcoll.x = position.getXp();
	strcoll.y = position.getYp();
	strcoll.w = &destRect.w;
	strcoll.h = &destRect.h;	
	strcoll.typ = &typ;
	strcoll = _h.strcoll;
	
	
	targ = Target(rend, strcoll.x, strcoll.y, position.getD());
}

bool Hero::moveX(int _mx) {
	
	if ( platform_check_move( _mx ) != 1)
		return false;
		
	if ( _mx != 0)
		nextPosture(_mx);
	targ.moveX(_mx);
	return position.moveX(_mx, heroSprite[0][actPosture].w/HERO_SCALE);
}

bool Hero::moveY(int _my) {
	
	if ( platform_check_move( 0, _my ) != 1)
		return false;
	
	if ( position.moveY(_my, heroSprite[0][actPosture].h/HERO_SCALE) ) {
		
		if ( position.getD() == left )
			nextPosture(-1);
		else
			nextPosture(1);
			
		targ.moveY(_my);
		
		return true;
	}
	else
		return false;
}

bool Hero::moveAll(int _mx, int _my) {
	bool tx = moveX(_mx);
	bool ty = moveY(_my);
	
	if ( tx ^ ty )
		return true;
	else if ( tx | ty )
		return true;
	else 
		return false;
}

bool Hero::move( int _mx, int _my) {
	
	speedX = _mx;
	
	speedY = _my; 
	
	return true;

}

void Hero::fire() {
	
//std::cout << "Fire In: " <<  bulletNumber << std::endl;
	
	Bullet tempBull [bulletNumber];

	for ( int i = 0; i < bulletNumber; ++i)
	{
		tempBull[i] = arrBullets[i];
	}

	delete [] arrBullets;

	bulletNumber++;
	arrBullets = new Bullet[bulletNumber];

	sPosition tempPos = position.getPosition();
		tempPos.x = position.getPosition().x + (position.getD() == left ? (-1 * (bulletSprite[0].w + 5)) : 154/HERO_SCALE + 5);
		tempPos.y = position.getPosition().y + 106/HERO_SCALE;
	
		
	arrBullets[bulletNumber-1] = Bullet( rend, tempPos, targ.getangle() );
		
	for ( int i = 0; i < bulletNumber-1 ; ++i)
	{
		arrBullets[i] = tempBull[i];
	}
//std::cout << "Fire Out: " <<  bulletNumber << std::endl;
}


void Hero::fireRewrite( int & _num ) {
//std::cout << "Come in: FIREREWIRITE: " << bulletNumber << '\n';
	if ( bulletNumber == 0 )
		return;
	bulletNumber--;
	
	Bullet * temp = new Bullet[bulletNumber];
	int o = 0;
	int u = 0;
	for ( ; o <= bulletNumber; ++o , ++u)
	{
		if ( o == _num )
		{
			u--;
			continue;
		}
		temp[u] = arrBullets[o];
	}
	delete [] arrBullets;
	arrBullets = temp;
	_num--;
//std::cout << "Come out: FIREREWIRITE: " <<  bulletNumber << std::endl;
	
}

bool Hero::checkCollision() {

bool boo = coll.checkCollision( );	

return boo;
}

sPosition * Hero::getPosition() {
	return position.getPositionPointer();
}

void Hero::show() {

	speedY += (speedY == 0? GRAVITY: 0);

	if ( speedX != 0 || speedY != 0 )
		moveAll(speedX, speedY);
	
	if ( position.getD() == left )
	{
		destRect.x = position.getX();
		destRect.y = position.getY();
		destRect.w = heroSprite[0][actPosture].w/HERO_SCALE;
		destRect.h = heroSprite[0][actPosture].h/HERO_SCALE;	
	
		SDL_RenderCopy(rend, tex, &heroSprite[0][actPosture], &destRect);
	}
	else if	( position.getD() == right )
	{
		destRect.x = position.getX();
		destRect.y = position.getY();
		destRect.w = heroSprite[1][actPosture].w/HERO_SCALE;
		destRect.h = heroSprite[1][actPosture].h/HERO_SCALE;	
	
		SDL_RenderCopy(rend, tex, &heroSprite[1][actPosture], &destRect);
	}
	
	targ.show();
	
	if ( bulletNumber > 0 ) 
	{
		for ( int e = 0; e < bulletNumber; ++e )
		{
			if ( arrBullets[e].isVisible() == true )
				arrBullets[e].show();
			else
			{
				fireRewrite(e);				
			}
		}
	}
	
}
void Hero::showStrColl() {
	std::cout << "x: " << strcoll.x << " y: " << strcoll.y
	<< " w: " << strcoll.w << " h: " << strcoll.h << std::endl;
	std::cout << "*x: " << *strcoll.x << " *y: " << *strcoll.y
	<< " *w: " << *strcoll.w << " *h: " << *strcoll.h << std::endl;
}


void Hero::nextPosture(int _mv) {
	if ( _mv != 0)
		_mv < 0 ? position.setD(left) : position.setD(right);
	
	actPosture++;
	if ( actPosture > 2)
		actPosture = 0;
}


Hero & Hero::operator=(const Hero & _h) {
	
	if ( this == &_h )
		return *this;
		
	position = _h.position;	
	
	
	
	bulletNumber = _h.bulletNumber;
	
	rend = _h.rend;	
	
	int len = std::strlen(_h.name);
	name = new char[len + 1];
	std::strcpy(name, _h.name);
	
	len = std::strlen(_h.sprite);	
	sprite = new char[len + 1];
	std::strcpy(sprite, _h.sprite);
	 
	SDL_Surface * surf = SDL_LoadBMP(sprite);

	Uint32 colorkey = SDL_MapRGB(surf->format,255,12,255);

	SDL_SetColorKey(surf,SDL_TRUE,colorkey);

	tex	= SDL_CreateTextureFromSurface(rend, surf);

	SDL_FreeSurface(surf);
	
	actPosture = _h.actPosture;
	
	speedX = _h.speedX;
	speedY = _h.speedY;
	angle = _h.angle;
	health = _h.health;
	armor = _h.armor;		
	typ = _h.typ;
	
	strcoll = _h.strcoll;
	return *this;
	
}

bool Hero::platform_check_move( int _mx, int _my ) {
	
	int numb = plat->get_plat_number();
	
	sPosition * pos = position.getPositionPointer();
	
	stc_platform * pl = plat->get_plat();
	
	for ( int i = 0; i < numb; ++i ) {
		
		if (   ( ( pos->x + _mx + heroSprite[0][0].w/HERO_SCALE ) >= pl[i].x )   &&   ( pos->x + _mx <= pl[i].x + pl[i].len )   
				&& (pos->y + _my + heroSprite[0][0].h/HERO_SCALE) >= pl[i].y  &&  (pos->y + _my <= pl[i].y + pl[i].thi) ) {
					
					return false;
				}
		
	}
	
	return true;
}


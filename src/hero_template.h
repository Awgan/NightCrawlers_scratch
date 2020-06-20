#ifndef HERO_H_
#define HERO_H_

#include <SDL2/SDL.h>

#include "bullet.h"
#include "library.h"
#include "position.h"

class Hero
{
	private:
		Position position;
		
		int bulletNumber;
		Bullet * arrBullets;		
		
		SDL_Renderer * rend;
		SDL_Texture * tex;
		
		char * name;		
		char * sprite;
		
		int actPosture;
		
		int speedX;
		int speedY;
		int health;
		int armor;
		
		void nextPosture(int _mv);
				
	protected:
		
		bool moveX(int _mx);
		bool moveY(int _my);
		bool moveAll(int _mx, int _my = 0);
		
	public:
		Hero();
		~Hero();
		
		Hero(SDL_Renderer * _rend, const char * _name, const sPosition & _pos);
		Hero(const Hero & _h);
		
		bool move( int _mx, int _my = 0);
		
		void fire();
		void fireRewrite( int & _num ) ;
		void show();
		
			
	
	
};

#endif

#ifndef HERO_H_
#define HERO_H_

#include <SDL2/SDL.h>

#include "everything.h"
#include "bullet.h"
#include "collision.h"
#include "library.h"
#include "platform.h"
#include "position.h"
#include "target.h"

class Hero : virtual public Everything
{
	private:
		Position position;
		Collision coll;
		Collision::strColl strcoll;
		Collision::collType typ;
		
		int bulletNumber;
		Bullet * arrBullets;		
		
		SDL_Renderer * rend;
		SDL_Texture * tex;
		
		char * name;		
		char * sprite;
		
		
		bool active;
		int actPosture;
		
		SDL_Rect destRect;
		
		
		int speedX;
		int speedY;
		double angle;
		int health;
		int armor;
		
		void nextPosture(int _mv);
		
		Target targ;
		
		Platform * plat;
			
	protected:
		
		bool moveX( int _mx );
		bool moveY( int _my );
		bool moveAll( int _mx, int _my = 0 );
		
		bool platform_check_move( int _mx, int _my = 0 );
		
	public:
		Hero();	
		~Hero();
		
		Hero(SDL_Renderer * _rend, const char * _name, const sPosition & _pos, Platform * _plat);
		Hero(const Hero & _h);
		
		
		bool checkCollision(); 
		sPosition * getPosition();
		void fire();
		void fireRewrite( int & _num ) ;
		
		bool move( int _mx, int _my = 0);
		void rotate(const int & _r) {targ.rotate(_r);}
		void show();
		void showStrColl();
		const Collision::strColl & getstrcoll() {return strcoll;};
		
		Hero & operator=( const Hero & _h);
	
};

#endif

#ifndef BULLET_H_
#define BULLET_H_

#include "everything.h"
#include "collision.h"
#include "library.h"
#include "position.h"

class Bullet : private Position, public Everything
{
	
	private:
		Collision coll;
		Collision::strColl strcoll;
		
		SDL_Renderer * rend;
		SDL_Texture * tex;
		SDL_Rect destRect;
		
		char * sprite;		
		int speed;
		bool visible;
		double angle;
		
		Collision::collType typ;
		
		
	protected:
	
	public:
		Bullet();	
		~Bullet();
		
		Bullet(SDL_Renderer * _rend, const sPosition _pos, const double & _ang);
		
		sPosition getPosition() {return getPosition();}
		sPosition * getPositionPointer() { return Position::getPositionPointer(); };
		
		bool checkCollision() {return coll.checkCollision();}
		int getSpeed() {return speed;}
		virtual const Collision::strColl & getstrcoll() {return strcoll;};	
		bool isVisible() {return visible;}
		
		void setLimX(int _lx) {Position::setLimX(_lx);}
		void setSpeed(int _sp) {speed = _sp;}
		void setPositionXY(int _x, int _y) {Position::setX(_x); Position::setY(_y);}
			
		void moveAuto();		
		void show();
		
		Bullet & operator=(const Bullet & _bull);
		
	
	
};

#endif

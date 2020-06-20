#ifndef POSITION_H_
#define POSITION_H_

#include "library.h"
#include "platform.h"



struct sPosition {
	int x;
	int y;
	dirc d;
	
	int limX;
	int limY;
};


class Position
{
	protected:
				
	
	private:
		sPosition pos;
		double angle;
	
	public:
		Position();
		~Position();
		
		Position(int _x, int _y, dirc _d, int _lx, int ly);
		Position(const sPosition & _sp);
		Position(const Position & _p);
		
		int getAngle() {return angle;}
		const int getX() {return pos.x;}
		const int getY() {return pos.y;}		
		int* getXp() {return &pos.x;}
		int* getYp() {return &pos.y;}
		dirc getD() {return pos.d;}
		int getLimX() {return pos.limX;}
		int getLimY() {return pos.limY;}
		sPosition getPosition() {return pos;} 
		sPosition * getPositionPointer() {return &pos;} 

		bool moveX(int _mx, int _safeBuf = 0);
		bool moveY(int _my, int _safeBuf = 0);
		bool move(int _speed, double _ang, int _safeBuf = 0  );
		
		void setAngle(double _a) { angle = _a;}
		bool setX(int _sx);
		bool setY(int _sy);
		void setD(dirc _sd) {pos.d = _sd;}
		void setLimX(int _lx) {pos.limX = _lx;}
		void setLimy(int _ly) {pos.limY = _ly;}
		
};

#endif





#ifndef EVERYTHING_H_
#define EVERYTHING_H_

#include "collision.h"

class Everything
{
	private:
	
	
	public:
		Everything () {};
		virtual ~Everything() {};
		virtual void show() = 0;
		virtual void fire() {};
		virtual const Collision::strColl & getstrcoll() = 0;
		virtual bool checkCollision() {return false;};
		virtual bool move(int, int = 0) {return false;};
		virtual void rotate(const int & _r) {return;};
	
};


#endif

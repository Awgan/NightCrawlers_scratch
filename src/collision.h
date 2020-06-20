#ifndef COLLISION_H_
#define COLLISION_H_

#include <stddef.h>

class Collision {
	
	public:
		
		
		enum collType { none, hero, bullet, platform };
		
		//structure for collecting position and dimension of each object
		//which is shown
		struct strColl {
			int * x = NULL;
			int * y = NULL;
			int * w = NULL;
			int * h = NULL; 
			
			collType * typ;
			
			strColl & operator=(const strColl & _sc );
			strColl * operator=(strColl * _sc);
		};
		
		
	
	private:
		//static array which gathers all object's structures
		static strColl * * arrColl;
		
		//static variable for saving size of the array
		static int 	arrSize;
		
		//unic number for object; the number points position in the array
		int id_number;
		collType typ;
		static int * * arrId;
		Collision();
		Collision( const Collision & _coll );
	
	public:	
		
		Collision( strColl * _scoll );
		
		
		virtual ~Collision();
	
		Collision & operator=(const Collision & _coll);
		
		//get pointer to array of pointers and array size
		void get( strColl * * * _tab, int * _size);
		
		void show();
		
		bool checkCollision();
	
	
};


#endif

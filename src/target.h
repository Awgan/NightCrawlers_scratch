#ifndef TARGET_H_
#define TARGET_H

#include <SDL2/SDL.h>
#include "library.h"
#include "position.h"

class Target 
{
	private:
		struct target_str {
			double angle;
			double dist;
			double x;		
			double y;
			int * x_cen;	//coordinate of the hero
			int * y_cen;	//coordinate of the hero
			dirc d;
		} target;
		
		void xy_calc();
		void angle_calc();
		char * sprite; 
		bool visible;

		SDL_Renderer * rend;
		SDL_Texture * tex;
		SDL_Rect rect;

	public:
		Target();		
		Target(SDL_Renderer * _rend, int * _cX, int * _cY, dirc _d);
		~Target();
		Target( const Target & _t );
		
		void moveX(int _mv); 	
		void moveY(int _mv);
		void rotate(int _deg);
		double getangle();
		void visibility(bool _b){visible = _b;}
		void show();
		
		Target & operator=(const Target & _t );	
};

//TODO




#endif

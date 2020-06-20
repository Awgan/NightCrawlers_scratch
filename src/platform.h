#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <SDL2/SDL.h>


struct stc_platform {
	int x;
	int y;
	int len;		//lenght
	int thi;		//thickness
	int mld;		//max load
};



class Platform {
	
	private :
		stc_platform * plat;
		int plat_no;
		SDL_Renderer * rend;
		SDL_Texture * tex;
		SDL_Rect * heroRect;		//delete?
		
		
	public:
		Platform () {};
		~Platform ();
		Platform ( const char * file, SDL_Renderer * _rend );
		
		
		
		bool check(SDL_Rect * _rec);
		bool check_2(SDL_Rect * _rec);
		void draw();
		void show_plat( int _n );
		unsigned char get_plat_number();
		stc_platform * get_plat();
	
	
};

#endif

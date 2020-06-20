#include <SDL2/SDL.h>
#include "hero.h"

void move_hero_loop( SDL_Event * even, Hero & _hero) {
	
	if ( even->key.type == SDL_KEYDOWN )
			switch (even->key.keysym.sym) {
				case SDLK_UP :
				_hero.move(0,-1 * MOVE_SPEED);
				break;
				case SDLK_DOWN :
				_hero.move(0,1 * MOVE_SPEED);
				break;
				case SDLK_LEFT :
				_hero.move(MOVE_L);
				break;
				case SDLK_RIGHT :
				_hero.move(MOVE_R);
				break;
				default :
				break;				
			}
		
		if ( even->key.type == SDL_KEYUP )
			switch (even->key.keysym.sym) {
				case SDLK_UP :
				_hero.move(0);
				break;
				case SDLK_DOWN :
				_hero.move(0);
				break;
				case SDLK_LEFT :
				_hero.move(0);
				break;
				case SDLK_RIGHT :
				_hero.move(0);
				break;
				default :
				break;				
			}
}


#include <SDL2/SDL.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "library.h"
#include "hero.h"
#include "platform.h"
#include "position.h"

struct gang_box {
			int ile_all;
			int il1;		//how many remain in team
			int il2;
			int act1;		//which one hero is select
			int act2;	
			team act_team;	//which group is select	
			Everything * * gang[2];
		};

void move_hero_loop( SDL_Event * even, gang_box * _gb, Platform * _plat);
void background_loop( SDL_Renderer * _rend, const char * _back);
//void collision( collisionSize * tab[], int _n );
void hero_select(const SDL_Event * _ev, gang_box * _gb);
void fire_loop(SDL_Event * even, gang_box * _gb);
void gravity( Everything * _hr );

void tim_er( gang_box * _gb );

/*void show_position(sPosition * _sp) {
	
	std::cout << "x: " << _sp->x << " & y: " << _sp->y << " (" << _sp->d << ")" << std::endl;
}*/

/*void show_collsize(collisionSize * _cs) {
	
	std::cout << "x: " << *_cs->x << " & y: " << *_cs->y << "w: " << *_cs->w << " & h: " << *_cs->h << std::endl;
}*/

int main( int argc, char * argv[] ) {
	
	SDL_Window * win;
	SDL_Renderer * rend;
	SDL_Event even;
	SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
		
	SDL_Init( SDL_INIT_EVERYTHING );
	win = SDL_CreateWindow("NightCrawlers", 0,0,640,480,SDL_WINDOW_OPENGL);
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	gang_box gbox;
		gbox.ile_all = 10;
		gbox.il1 = gbox.ile_all / 2;
		gbox.il2 = gbox.ile_all / 2;
		gbox.act1 = 1;
		gbox.act2 = 1;
		
		
	int maxW, maxH;
	SDL_GetWindowSize(win, &maxW, &maxH);
////////////////////////////////////////////////////////////////////////	
srand(time(NULL));

Platform platan( "./level01.txt", rend );
stc_platform * pl = platan.get_plat();
int pl_n = platan.get_plat_number();
	
	sPosition arrPosition [ gbox.ile_all ];
	/*sPosition arrPosition[ gbox.ile_all ] = {
		{rand()%601, rand()%441 ,right, maxW, maxH},
		{rand()%601, rand()%441 ,right, maxW, maxH},
		{rand()%601, rand()%441 ,right, maxW, maxH},
		{rand()%601, rand()%441 ,right, maxW, maxH},
		{rand()%601, rand()%441 ,right, maxW, maxH},
		{rand()%601, rand()%441 ,left, maxW, maxH},
		{rand()%601, rand()%441 ,left, maxW, maxH},
		{rand()%601, rand()%441 ,left, maxW, maxH},
		{rand()%601, rand()%441 ,left, maxW, maxH},
		{rand()%601, rand()%441 ,left, maxW, maxH}		
		};*/
	
	for ( int i = 0; i < gbox.ile_all; ++i ) {
		arrPosition[i] = {rand()%601, rand()%441 ,( ( i < (gbox.ile_all / 2) )?right:left ), maxW, maxH};
	
		for ( int j = 0; j < pl_n; ++j) {
			if ( ( ( arrPosition[i].x + heroSprite[0][0].w/HERO_SCALE ) >= pl[j].x )   &&   ( arrPosition[i].x <= pl[j].x + pl[j].len )   
					&& (arrPosition[i].y + heroSprite[0][0].h/HERO_SCALE) >= pl[j].y  &&  (arrPosition[i].y <= pl[j].y + pl[j].thi) ) {
						--i;
						break;
					}
		}
	}
	
	Everything * Team1[5];
	Everything * Team2[5];
	
		
		for( int i = 0; i < gbox.il1; i++ ) {
			Team1[i] = new Hero(rend, "red", arrPosition[i], &platan);
		}
		
		for(int i = 0 ; i < gbox.il2; ++i ) {
			Team2[i] = new Hero(rend, "green", arrPosition[i+5], &platan);
		}
			
			gbox.act_team = red;
			gbox.gang[red] = Team1;
			gbox.gang[green] = Team2;


SDL_GetTicks();



////////////////////////////////////////////////////////////////////////
//				Main Loop
////////////////////////////////////////////////////////////////////////	
//int st, en;

//start:		
	while( even.quit.type != SDL_QUIT && gbox.il1 > 0 && gbox.il2 > 0) {
//st = SDL_GetTicks();
		SDL_PollEvent(&even);
				 
		tim_er(&gbox);
		 
		
		if ( even.button.type == SDL_MOUSEBUTTONDOWN ) {
			hero_select(&even, &gbox);
		}
		
		if ( even.key.type == SDL_KEYDOWN || even.key.type == SDL_KEYUP ) {
			move_hero_loop( &even, &gbox, &platan);
			fire_loop(&even, &gbox);			
		}
	 
		SDL_RenderClear(rend);
	 
		//background_loop( rend, BACKGROUND );		
		
		for (int t = 0; t < gbox.il1; t++ ) {
			Team1[t]->show();
		}
		for (int t = 0; t < gbox.il2; t++ ) {
			Team2[t]->show();
		}
		
		
		for (int t = 0; t < gbox.il1; t++ ) {	
			if ( Team1[t]->checkCollision() ) {
				delete Team1[t];
				--gbox.il1;
				for (int i = t ; i < gbox.il1; ++i ) {
					Team1[i] = Team1[i+1];
				}								
				--gbox.ile_all;
				if (gbox.act1 >= gbox.il1)
					gbox.act1 = gbox.il1-1;
			}
		}
		for (int t = 0; t < gbox.il2; t++ ) {	
			if ( Team2[t]->checkCollision() ) {
				delete Team2[t];
				--gbox.il2;
				for (int i = t ; i < gbox.il2; ++i ) {
					Team2[i] = Team2[i+1];
				}								
				--gbox.ile_all;
				if (gbox.act2 >= gbox.il2)
					gbox.act2 = gbox.il2-1;
			}
		}
		platan.draw();	
		SDL_RenderPresent(rend);
	//en = SDL_GetTicks();
	//std::cout << "It last: " << en - st << " ms." << std::endl;	
	}
	
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	return 0;
}

void background_loop( SDL_Renderer * _rend, const char * _back)
{
	SDL_Surface * surf = SDL_LoadBMP(_back);
	SDL_Texture * tex = SDL_CreateTextureFromSurface(_rend, surf);
	SDL_RenderCopy(_rend, tex, NULL, NULL);
	SDL_DestroyTexture( tex );
	SDL_FreeSurface( surf );
}

void move_hero_loop( SDL_Event * even, gang_box * _gb, Platform * _plat) {
	
static unsigned int timeStart;
static unsigned int timeStop;

if ( even->key.type == SDL_KEYDOWN || even->key.type == SDL_KEYUP ) {
	int tt = int(_gb->act_team);
	int * act;
	act = (_gb->act_team == red) ? &_gb->act1 : &_gb->act2;		//how many heroes remain
 timeStart = SDL_GetTicks();
		if ( even->key.type == SDL_KEYDOWN ) {
			
			
			switch (even->key.keysym.sym) {
				case SDLK_UP :
				//if ( platform_check_move( _gb->gang[tt][*act], _plat->get_plat(), _plat->get_plat_number(), MOVE_U, 'U') )
					_gb->gang[tt][*act]->move(0, MOVE_U);
				break;
				case SDLK_DOWN :
				//if ( platform_check_move( _gb->gang[tt][*act], _plat->get_plat(), _plat->get_plat_number(), MOVE_D, 'D') )
					_gb->gang[tt][*act]->move(0, MOVE_D);
				break;
				case SDLK_LEFT :
				//if ( platform_check_move( _gb->gang[tt][*act], _plat->get_plat(), _plat->get_plat_number(), MOVE_L, 'L') )
					_gb->gang[tt][*act]->move(MOVE_L);
				break;
				case SDLK_RIGHT :
				//if ( platform_check_move( _gb->gang[tt][*act], _plat->get_plat(), _plat->get_plat_number(), MOVE_R, 'R') )
					_gb->gang[tt][*act]->move(MOVE_R);
				break;
				case SDLK_q :
				_gb->gang[tt][*act]->rotate(1 * ROTATE);
				break;
				case SDLK_a : 
				_gb->gang[tt][*act]->rotate(-1 * ROTATE);
				break;
				case SDLK_w :
				_gb->gang[tt][*act]->move(0);
				*act = ( 1 + (*act) ) % ( _gb->act_team == red ? _gb->il1 : _gb->il2 );
				
				break;
				default :
				break;				
			}
		}
		
		if ( even->key.type == SDL_KEYUP) { 
			switch (even->key.keysym.sym) {
				case SDLK_UP :
				_gb->gang[tt][*act]->move(0);
				break;
				case SDLK_DOWN :
				_gb->gang[tt][*act]->move(0);
				break;
				case SDLK_LEFT :
				_gb->gang[tt][*act]->move(0);
				break;
				case SDLK_RIGHT :
				_gb->gang[tt][*act]->move(0);
				break;
				case SDLK_q :
					_gb->gang[tt][*act]->rotate(0);
				break;
				case SDLK_a : 
					_gb->gang[tt][*act]->rotate(0);
				default :
				break;				
			}
		even->type = SDL_MOUSEMOTION; 	//if SDL_KEYUP is last event type, it will run the loop	
		SDL_PushEvent(even);			//it set diffrent type, to prevent run the loop indefinitely
	}
}
timeStop = SDL_GetTicks();
if ( timeStop - timeStart < 30 )
	SDL_Delay(timeStop - timeStart);
}

void hero_select(const SDL_Event * _ev, gang_box * _gb) {
	
	if ( _ev->button.type != SDL_MOUSEBUTTONDOWN  && _ev->button.button != SDL_BUTTON_LEFT )
		return;
	int mx = _ev->button.x;	
	int my = _ev->button.y;
	
	int thisx;
	int thisy;
	int thisw;
	int thish;
	
	int tt = _gb->act_team;
	int max = ( tt == red ? _gb->il1 : _gb->il2 );
	int * act;
	act = (_gb->act_team == red) ? &_gb->act1 : &_gb->act2;	
	
	for ( int i = 0; i < max; ++i ) {
		thisx = *(_gb->gang[tt][i]->getstrcoll().x);
		thisy = *(_gb->gang[tt][i]->getstrcoll().y);
		thisw = *(_gb->gang[tt][i]->getstrcoll().w);
		thish = *(_gb->gang[tt][i]->getstrcoll().h);
		
		if (mx >= thisx && mx <= thisx + thisw && my >= thisy && my <= thisy + thish) {
			_gb->gang[tt][*act]->move(0);
			*act = i;
			_gb->gang[tt][*act]->move(0);
			return;
		}
	
	}
}


void fire_loop(SDL_Event * even, gang_box * _gb) {
	if ( even->type == SDL_KEYDOWN ) {
		
		int tt = _gb->act_team;
		int act = 0;
		act = (_gb->act_team == red) ? _gb->act1 : _gb->act2;
		
		switch (even->key.keysym.sym) {
				case SDLK_f :
					_gb->gang[tt][act]->fire();
					_gb->gang[tt][act]->move(0);
					if ( _gb->act_team == red )
						_gb->act_team = green;
					else
						_gb->act_team = red;
				break;
				default:
				break;
		}
	}
}

void gravity( Everything * _hr ) {
	
	_hr->move( 0, 0 );
	
}



void tim_er( gang_box * _gb ) {
	static unsigned long long int start = SDL_GetTicks();
	static team prev_team = _gb->act_team;
	
	if ( _gb->act_team != prev_team ) {
		start = SDL_GetTicks();
		prev_team = _gb->act_team;
	}
	
	if ( SDL_GetTicks() - start > 5000 ) {
		int act = (_gb->act_team == red) ? _gb->act1 : _gb->act2;
		_gb->gang[_gb->act_team][act]->move(0);
		_gb->act_team =( (_gb->act_team == red) ? green : red );
		prev_team = _gb->act_team;
		start = SDL_GetTicks();
	}
	
	
}


/*
	int thisx = *(arrColl[id_number]->x);
	int thisy = *(arrColl[id_number]->y);
	int thisw = *(arrColl[id_number]->w);
	int thish = *(arrColl[id_number]->h);
		
	for ( int i = 0; i < arrSize; ++i ) {
		if ( i == id_number )
			continue;
		
		int ax = *(arrColl[i]->x);
		int ay = *(arrColl[i]->y);
		int aw = *(arrColl[i]->w);
		int ah = *(arrColl[i]->h);
		
		if ( thisx + thisw >= ax && thisx <= ax + aw && thisy +thish >= ay && thisy <= ay + ah ) {
			std::cout << "HIT HIT HIT\n";
			return true;
		}
	}*/



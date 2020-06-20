
#include <iostream>
#include <fstream>
#include <string>

#include "library.h"
#include "platform.h"

//stc_platform * Platform::plat = new stc_platform[0];

Platform::~Platform() {
	delete [] plat;	
}

Platform::Platform ( const char * _file_name, SDL_Renderer * _rend ) {
	
	rend = _rend;
	//tex = NULL;
	SDL_Surface * surf = SDL_LoadBMP( SPRITES[ 6 ] ); 
	Uint32 colorkey = SDL_MapRGB( surf->format, 255, 0, 255 );
	SDL_SetColorKey( surf, SDL_TRUE, colorkey );	
	
	tex = SDL_CreateTextureFromSurface( rend, surf );
	
	SDL_FreeSurface( surf );


	
/**********************
 * level file parsing *
 **********************/	
	std::string line;
	std::ifstream file;
	file.open( _file_name );
	
	plat_no 		= 0;
	int plat_next	= 0;
	
	while ( std::getline( file, line ) ) {
		
		if ( line[0] == '#' )
			continue;
		
		if ( ( line.find( "platform", 0 ) != std::string::npos ) ) {
			int last = line.std::string::find_last_of( " " );
			last = last + 1;
			plat_no = std::stoi( line.std::string::substr( last ) );
			//std::cout << "plat_no: " << plat_no << '\n';
			//delete [] plat;
			plat = new stc_platform[plat_no];
			continue;
		}
		
		if (( line.find( ",", 0 ) != std::string::npos ) && plat_next < plat_no ) {
			int a = 0;
			int b = line.find( ",", a );
			plat[plat_next].x = std::stoi( line.std::string::substr( a, b - a ) );
			
			a = b + 1;
			b = line.find( ",", a );
			plat[plat_next].y = std::stoi( line.std::string::substr( a, b - a ) );
			
			a = b + 1;
			b = line.find( ",", a );
			plat[plat_next].len = std::stoi( line.std::string::substr( a, b - a ) );
			
			a = b + 1;
			b = line.find( ",", a );
			plat[plat_next].thi = std::stoi( line.std::string::substr( a, b - a ) );
			
			a = b + 1;
			b = line.find( ",", a );
			plat[plat_next].mld = std::stoi( line.std::string::substr( a, b - a ) );
			show_plat( plat_next );
			
			plat_next++;
		}
		else if ( plat_next >= plat_no ) {
			std::cout << "Platform::Platform() : Too many lines with platform traits\n";
			break;
		}
		
	}
}

bool Platform::check(SDL_Rect * _rec) {
	
	for ( int i = 0; i <  plat_no; ++i ) {
		if ( _rec->y + _rec->h >= plat[i].y && _rec->x >= plat[i].x && _rec->x + _rec->w <= plat[i].x + plat[i].len )
			return true;
	}
	return false;
}

bool Platform::check_2(SDL_Rect * _rec) {
	
	for ( int i = 0; i <  plat_no; ++i ) {
		if ( _rec->y + _rec->h >= plat[i].y && _rec->x >= plat[i].x && _rec->x + _rec->w <= plat[i].x + plat[i].len )
			return true;
	}
	return false;
}

void Platform::draw() {
	
	SDL_Rect temp;
	
	for( int i = 0; i < plat_no; ++i ) {
		//std::cout << "plat_no::i " << i << '\n';
		temp.x = plat[i].x;
		temp.y = plat[i].y;
		temp.w = plat[i].len;
		temp.h = plat[i].thi;
		//std::cout << "no: " << plat_no << " x " << plat[i].x << " x " << plat[i].y << " x " << plat[i].len << " x " << plat[i].thi << std::endl; 
		
		SDL_RenderCopy( rend, tex, &wallSprite[0], &temp ); 
	}
}

void Platform::show_plat( int _n ) {
	std::cout << plat[_n].x << " " << plat[_n].y << " " << plat[_n].len << " " << plat[_n].thi << " " << plat[_n].mld <<'\n'; 
}

unsigned char Platform::get_plat_number() {
	
	return (unsigned char)plat_no;
	
}

stc_platform * Platform::get_plat() {
	
	return plat;
	
}

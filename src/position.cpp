#include <iostream>
#include <math.h>

#include "position.h"


Position::Position() {
	pos.x = 0;
	pos.y = 0;
	pos.d = center;

	pos.limX = pos.x;
	pos.limY = pos.y;

}

Position::~Position() {
	//std::cout << "POSITION: destruktor\n";
}

Position::Position(int _x, int _y, dirc _d, int _lx, int _ly) {
	pos.x = _x;
	pos.y = _y;
	pos.d = _d;

	pos.limX = _lx;
	pos.limY = _ly;	
}

Position::Position(const sPosition & _sp) {
	pos.x = _sp.x;
	pos.y = _sp.y;
	pos.d = _sp.d;

	pos.limX = _sp.limX;
	pos.limY = _sp.limY;
}

Position::Position(const Position & _p) {
	pos.x = _p.pos.x;
	pos.y = _p.pos.y;
	pos.d = _p.pos.d;

	pos.limX = _p.pos.limX;
	pos.limY = _p.pos.limY;
}


bool Position::moveX(int _mx, int _safeBuf) {
	if ( _mx != 0 )
		_mx < 0 ? setD(left) : setD(right);
	
	if ( pos.x + _mx >= 0 && pos.x + _mx + _safeBuf <= pos.limX ){
		pos.x += _mx;
		return true;
	}
	else
		return false;
}

bool Position::moveY(int _my, int _safeBuf) {
	if ( pos.y + _my >= 0 && pos.y + _my + _safeBuf <= pos.limY ){
		pos.y += _my;
		return true;
	}
	else
		return false;
}

bool Position::move(int _speed, double _ang, int _safeBuf ) { //for rotating object
	
	static int dx = 0;
	static int dy = 0;
	static int st_ang = 555;
	
	if ( st_ang != _ang ) {
		st_ang = _ang;
		dx = _speed * cos( _ang * (PI / 180) );
		dy = _speed * sin( _ang * (PI / 180) );
		
	}
	//std::cout << "angl: " << _ang << " dx: " << dx << " dy: " << dy << std::endl;
	if( ( pos.x + dx >= 0 && pos.x + dx + _safeBuf <= pos.limX ) && ( pos.y + dy >= 0 && pos.y + dy + _safeBuf <= pos.limY ) ) {
		pos.x += dx;
		pos.y += dy;
		return true;
	}
	return false;
	
}

bool Position::setX(int _sx) {
	if (_sx > 0 && _sx < pos.limX){
		pos.x = _sx;
		return true;
	}
	else
		return false;
}

bool Position::setY(int _sy) {
	if (_sy > 0 && _sy < pos.limY){
		pos.y = _sy;
		return true;
	}
	else
		return false;
}















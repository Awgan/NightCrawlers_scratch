
#include <iostream>
#include <stddef.h>
#include "collision.h"

Collision::strColl * * Collision::arrColl = new Collision::strColl * [0];
int * * Collision::arrId = new int * [0];
int Collision::arrSize = 0;

Collision::strColl & Collision::strColl::operator=(const strColl & _sc ) {
	//std::cout << "Collision::strColl & Collision::strColl::operator=\n";
	if ( this == &_sc )
		return *this;
	
	if ( x!= NULL && y!= NULL && w!= NULL && h!= NULL && _sc.x!= NULL && _sc.y!= NULL && _sc.w!= NULL && _sc.h!= NULL && _sc.typ != NULL) {
		*x = *_sc.x;
		*y = *_sc.y;
		*w = *_sc.w;
		*h = *_sc.h;
		
		*typ = *_sc.typ;
	}
	else
		std::cout << "Err: Some pointers have not beed initialized struct strColl\n";
	return *this;
}

Collision::strColl * Collision::strColl::operator=(strColl * _sc) {
	
//std::cout << "Collision::strColl * Collision::strColl::operator=(strColl * _sc)\n";
	
	if ( this == _sc )
		return this;
	return NULL;
}

Collision::Collision() {
	//std::cout << "Collision::Collision()\n";
	if ( arrSize == 0 ) {
		
		++arrSize;
		delete [] arrColl;
		delete [] arrId;
		arrColl = new strColl * [arrSize];
		arrId = new int * [arrSize];
		id_number = 0;
		arrColl[id_number] = NULL; // <-- can't manage with this; how to delete it if you use 'new artColl'?
		arrId[id_number] = &id_number;
		
	}
	else
	{
		++arrSize;
		id_number = arrSize - 1;
		
		strColl * * tempColl = new strColl * [arrSize];
		int * * tempId = new int * [arrSize];
		for ( int i = 0; i < arrSize - 1; ++i ) {
					
			tempColl[i] = arrColl[i];
			tempId[i] = arrId[i]; 
		}
		
		delete [] arrColl;
		arrColl = tempColl;		
		
		delete [] arrId;
		arrId = tempId;
		
		arrColl[id_number] = NULL; // <-- can't manage with this; how to delete it if you use 'new artColl'?
		arrId[id_number] = &id_number;		
	}

}

Collision::Collision( strColl * _scoll ) {
	//std::cout << "Collision::Collision( strColl * _scoll )\n";
	if ( arrSize == 0 ) {
		
		++arrSize;
		delete [] arrColl;
		delete [] arrId;
		arrColl = new strColl * [arrSize];
		arrId = new int * [arrSize];
		id_number = 0;
				
		arrColl[id_number] = _scoll;
		arrId[id_number] = &id_number;	
	}
	else
	{		
		++arrSize;
		id_number = arrSize - 1;
		
		strColl * * tempColl = new strColl * [arrSize];
		int * * tempId = new int * [arrSize];
		for ( int i = 0; i < arrSize - 1; ++i ) {
					
			tempColl[i] = arrColl[i];
			tempId[i] = arrId[i]; 
		}
		
		delete [] arrColl;
		arrColl = tempColl;		
		
		delete [] arrId;
		arrId = tempId;
			
		arrColl[id_number] = _scoll;
		arrId[id_number] = &id_number;		
	}
		
}

Collision::Collision( const Collision & _coll ) {
	//std::cout <<"Collision::Collision( const Collision & _coll )\n";
		
	++arrSize;
	id_number = arrSize - 1;
	
	strColl * * tempColl = new strColl * [arrSize];
	int * * tempId = new int * [arrSize];
	for ( int i = 0; i < arrSize - 1; ++i ) {
				
		tempColl[i] = arrColl[i];
		tempId[i] = arrId[i]; 
	}
	
	delete [] arrColl;
	arrColl = tempColl;		
	
	delete [] arrId;
	arrId = tempId;
		
	arrColl[id_number] = _coll.arrColl[_coll.id_number];
	arrId[id_number] = &id_number;
	
	
}

Collision::~Collision() {
	//std::cout <<"Collision::~Collision()\n";
	
	if ( arrSize == 1 ) {
		--arrSize;
		delete [] arrColl;
		delete [] arrId;
	}
	else {
		--arrSize;
		strColl * * tempcoll = new strColl * [arrSize];
		int * * tempId = new int * [arrSize];
		
		int i = 0;
		for ( ; i < arrSize && i != id_number; ++i ) {
			tempcoll[i] = arrColl[i];
			tempId[i] = arrId[i];		
		}
		for( ; i < arrSize; ++i ) {
			tempcoll[i] = arrColl[i + 1];
			tempId[i] = arrId[i + 1];
			*tempId[i] = *tempId[i] - 1;
		}
		delete [] arrColl;
		arrColl = tempcoll;
			
		delete [] arrId;
		arrId = tempId;
	}
}

Collision & Collision::operator=(const Collision & _coll) {
	//std::cout << "Collision::operator=\n";
	if ( this == & _coll )
		return *this;
		
	if ( arrColl[id_number] != NULL && _coll.arrColl[_coll.id_number] != NULL )
		*arrColl[id_number] = *_coll.arrColl[_coll.id_number];
	else
		std::cout << "Err: There is one or more NULL pointer for 'strColl * struct' in 'arrColl' array\n";
	
	return *this;
	
}

void fshow( const Collision::strColl * _t) {
	
	std::cout << *_t->x << " " << *_t->y << " " <<  *_t->w << " " << *_t->h;
	std::cout << std::endl;
}

bool Collision::checkCollision() {
	
	if ( arrSize == 0 ) 
		return false;
		
	int thisx = *(arrColl[id_number]->x);
	int thisy = *(arrColl[id_number]->y);
	int thisw = *(arrColl[id_number]->w);
	int thish = *(arrColl[id_number]->h);
	int thist = *(arrColl[id_number]->typ);
		
	for ( int i = 0; i < arrSize; ++i ) {
		if ( i == id_number || thist == *(arrColl[i]->typ)  )
			continue;
		
		int ax = *(arrColl[i]->x);
		int ay = *(arrColl[i]->y);
		int aw = *(arrColl[i]->w);
		int ah = *(arrColl[i]->h);
		
		/*std::cout << "i: " << i << std::endl;
		fshow(arrColl[id_number]);
		fshow(arrColl[i]);*/
		
		if ( thisx + thisw >= ax && thisx <= ax + aw && thisy + thish >= ay && thisy <= ay + ah ) {
			
			std::cout << "HIT HIT HIT\n";
			return true;
		}
	}
	
	return false;
}

void Collision::get( strColl * * * _tab, int * _size) {
		
		*_tab = arrColl;
		*_size = arrSize;
		
}

void Collision::show() {
std::cout << "void Collision::show()\n";
std::cout << "arrSize: " << arrSize << '\n';
	for ( int r = 0; r < arrSize; ++r ) {
		
		std::cout << "id number: " << r << ", strColl pointer to: " << arrColl[r] << std::endl;
		if ( arrColl[r] != NULL ) {
			std::cout << "                " << arrColl[r]->x << " " << arrColl[r]->y << " " << arrColl[r]->w << " " << arrColl[r]->h << std::endl;
			std::cout << "                " << *arrColl[r]->x << " " << *arrColl[r]->y << " " << *arrColl[r]->w << " " << *arrColl[r]->h << std::endl;
		}
	}
	
}









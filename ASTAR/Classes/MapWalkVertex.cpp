#include "MapWalkVertex.h"

MapWalkVertex::MapWalkVertex(){
	
}

MapWalkVertex::~MapWalkVertex(){

}

bool MapWalkVertex::init(){
	if(!Node::init()){
		return false;
	}

	m_pGraphVertex=nullptr;

	return true;
}
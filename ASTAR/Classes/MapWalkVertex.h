#ifndef _MAP_WALK_VERTEX_H_
#define _MAP_WALK_VERTEX_H_
#include "cocos2d.h"

USING_NS_CC;

class Vertex;

class MapWalkVertex : public Node{
public:
	MapWalkVertex();
	~MapWalkVertex();
	bool init();
	CREATE_FUNC(MapWalkVertex);

	void SetGraphVertex( Vertex * Var ) { m_pGraphVertex = Var ; };
	Vertex* GetGraphVertex( ) { return m_pGraphVertex ; };
private:
	Vertex* m_pGraphVertex;
};


#endif
#ifndef _SPFA_H_
#define _SPFA_H_
#include "GraphPathFinding.h"

class SPFA : public GraphPathFinding{
public:
	SPFA();
	~SPFA();

	//override
	void  execute(const Graph& Graph , const string& VetexId ) override ;
private:

	inline bool Relax( Vertex* pStartVertex , Vertex* pEndVertex , int Weight ) ;
};
#endif
/*
这里介绍并实践经典的Dijkstra算法。Dijkstra的执行类似BFS（广度优先搜索），并且使用了贪心策略。很多最短路径算法都使用了一种叫做“松弛（Relax）”操作，Dijkstra也不例外
*/

#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "GraphPathFinding.h"

class Dijkstra : public GraphPathFinding{
public:
	Dijkstra();
	~Dijkstra();

	//override
	void  execute(const Graph& Graph , const string& VetexId ) override ;

	inline Result& getResult(){
		return m_result;
	};
private:
	// 获得(提取)最小路径估值的顶点
	inline Vertex* ExtractMin( vector< Vertex* >& Q ) ;

	// 松弛
	inline void Relax( Vertex* v1 , Vertex* v2 , int Weight ) ;
private:
	Result m_result;

};
#endif
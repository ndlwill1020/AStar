#ifndef _GRAPH_PATH_FINDING_H_
#define _GRAPH_PATH_FINDING_H_
#include "Graph.h"
#include <unordered_map>
using namespace std;

/*
	路径搜索结果
*/
struct Result
{
	// 路径树
	unordered_map< Vertex* , Vertex* > PathTree ;
};

class GraphPathFinding{
public:
	GraphPathFinding();
	~GraphPathFinding();
	virtual void execute(const Graph& graph,const string& vertexId) = 0;
};
#endif
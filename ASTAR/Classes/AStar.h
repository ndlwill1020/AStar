/*
Dijsktra : 选出一个具有最小路径代价的顶点，松弛其所有的边。
　　SPFA : 用一个队列存放顶点，从队列中取出队头顶点，松弛其所有边，如果松弛成功，边上顶点入队。
　　A* : 是Djikstra的改进版。选出具有启发式函数值最小的顶点，松弛其所有的边。

  Dijkstra要比BFS聪明，BFS只是“盲目地”从队列中取出元素出来扩展，Dijkstra则知道每次应该选取路径代价最短的节点扩展。

  A*通过一个叫“启发式函数”的东东来改进扩展规则，它会尽量避免扩展其他无用的顶点，它的目标就是朝着目的地直奔而去的。这样说，好像A*长了眼睛一样能看到当前位置距离目标点还有多远。A*和上面的Dijkstra最大的区别就是有“眼睛”：启发式函数。
*/

#ifndef _ASTAR_H_
#define _ASTAR_H_
#include "GraphPathFinding.h"
#include <functional>
using namespace std;

class AStar : public GraphPathFinding{
public:
	// 估计顶点到目标顶点的代价
	AStar();
	~AStar();

	//估价函数变量 Ｈ函数（估计当前顶点到目标顶点的代价）
	/*
	Ｈ函数（估计当前顶点到目标顶点的代价）”外包“到外部执行了。因为AStart类是不知道MapWalkVertex顶点类的存在的。为什么要”外包“执行，而不是在AStar类中做呢？如果要在AStar类中做，就需要知道每个顶点的几何位置，而顶点的几何位置是Cocos2D-x的Node类的属性。AStar类不应该和其他东西耦合，为了”独立“，”通用“，计算Ｈ就用观察者模式思想，”外包“执行了。
	*/
	function<int( const Vertex* pVCurrent , const Vertex* pVTarget ) > estimate ; //看成一个成员变量 相当于函数指针变量
	virtual void execute( const Graph& Graph , const string& VetexId ) override ;

	void SetTarget( Vertex* pVTarget ){
		m_pVTarget = pVTarget;
	};
private:
	// 抽出最小路径估值的顶点
	inline Vertex* ExtractMin( vector< Vertex* >& Q ) ;

	// 松弛
	inline bool Relax( Vertex* v1 , Vertex* v2 , int Weight ) ;

	
private:
	//目标点
	Vertex* m_pVTarget ;
};
#endif
/*
������ܲ�ʵ�������Dijkstra�㷨��Dijkstra��ִ������BFS���������������������ʹ����̰�Ĳ��ԡ��ܶ����·���㷨��ʹ����һ�ֽ������ɳڣ�Relax����������DijkstraҲ������
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
	// ���(��ȡ)��С·����ֵ�Ķ���
	inline Vertex* ExtractMin( vector< Vertex* >& Q ) ;

	// �ɳ�
	inline void Relax( Vertex* v1 , Vertex* v2 , int Weight ) ;
private:
	Result m_result;

};
#endif
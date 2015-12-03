/*
Dijsktra : ѡ��һ��������С·�����۵Ķ��㣬�ɳ������еıߡ�
����SPFA : ��һ�����д�Ŷ��㣬�Ӷ�����ȡ����ͷ���㣬�ɳ������бߣ�����ɳڳɹ������϶�����ӡ�
����A* : ��Djikstra�ĸĽ��档ѡ����������ʽ����ֵ��С�Ķ��㣬�ɳ������еıߡ�

  DijkstraҪ��BFS������BFSֻ�ǡ�äĿ�ء��Ӷ�����ȡ��Ԫ�س�����չ��Dijkstra��֪��ÿ��Ӧ��ѡȡ·��������̵Ľڵ���չ��

  A*ͨ��һ���С�����ʽ�������Ķ������Ľ���չ�������ᾡ��������չ�������õĶ��㣬����Ŀ����ǳ���Ŀ�ĵ�ֱ����ȥ�ġ�����˵������A*�����۾�һ���ܿ�����ǰλ�þ���Ŀ��㻹�ж�Զ��A*�������Dijkstra������������С��۾���������ʽ������
*/

#ifndef _ASTAR_H_
#define _ASTAR_H_
#include "GraphPathFinding.h"
#include <functional>
using namespace std;

class AStar : public GraphPathFinding{
public:
	// ���ƶ��㵽Ŀ�궥��Ĵ���
	AStar();
	~AStar();

	//���ۺ������� �Ⱥ��������Ƶ�ǰ���㵽Ŀ�궥��Ĵ��ۣ�
	/*
	�Ⱥ��������Ƶ�ǰ���㵽Ŀ�궥��Ĵ��ۣ�����������ⲿִ���ˡ���ΪAStart���ǲ�֪��MapWalkVertex������Ĵ��ڵġ�ΪʲôҪ�������ִ�У���������AStar�������أ����Ҫ��AStar������������Ҫ֪��ÿ������ļ���λ�ã�������ļ���λ����Cocos2D-x��Node������ԡ�AStar�಻Ӧ�ú�����������ϣ�Ϊ�ˡ�����������ͨ�á�������Ⱦ��ù۲���ģʽ˼�룬�������ִ���ˡ�
	*/
	function<int( const Vertex* pVCurrent , const Vertex* pVTarget ) > estimate ; //����һ����Ա���� �൱�ں���ָ�����
	virtual void execute( const Graph& Graph , const string& VetexId ) override ;

	void SetTarget( Vertex* pVTarget ){
		m_pVTarget = pVTarget;
	};
private:
	// �����С·����ֵ�Ķ���
	inline Vertex* ExtractMin( vector< Vertex* >& Q ) ;

	// �ɳ�
	inline bool Relax( Vertex* v1 , Vertex* v2 , int Weight ) ;

	
private:
	//Ŀ���
	Vertex* m_pVTarget ;
};
#endif
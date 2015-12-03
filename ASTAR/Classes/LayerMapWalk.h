#ifndef _LAYER_MAP_WALK_H_
#define _LAYER_MAP_WALK_H_
#include "cocos2d.h"
USING_NS_CC;
#include "Graph.h"
#include "Role.h"

#include <vector>
using namespace std;

//#include "LayerHudControl.h"
//#include "MapWalkVertex.h"

class LayerHudControl;
class MapWalkVertex;
class Graph;

class LayerMapWalk : public Layer{
	friend class LayerHudControl;
	friend class MapWalkConfigManager;
public:
	enum OperationMode{
		//  ���ö���
		PutVertex , 
		// ��ҷ����
		DragContent ,
		// ��ҷ��
		DragEdge , 
		// ���ý�ɫ
		PositionRole , 
		// ����
		RoleWalk , 
	};

	LayerMapWalk();
	~LayerMapWalk();

	bool onTouchBegan( Touch *touch , Event *unused_event ); 

	void onTouchMoved( Touch *touch , Event *unused_event ); 

	void onTouchEnded( Touch *touch , Event *unused_event );

	// �ж��Ƿ����ж���
	// �������еĶ����ָ�롣û���У�����0
	MapWalkVertex* HitMapWalkVertex( const Vec2& pos )  ; 

	// ���һ������
	void AddVertex( MapWalkVertex* pMwv , const char * pszId = 0 ) ;
	// ���һ����
	void AddEdge( MapWalkVertex* pMwv1 , MapWalkVertex* pMwv2 ) ; 

	// ����һ������ֱ��
	static void MakeLine( Sprite* pSpr , const Point& pt1 , const Point& pt2 );

	LayerHudControl * m_LayerHudControl; 

	OperationMode m_Mode ; 

	bool init();
	CREATE_FUNC(LayerMapWalk);

private:
	void StartWalk( const vector< MapWalkVertex* >& GvSeq ) ; 
private:

	Graph* m_pGraph;

	Role* m_pRole ; 

	
	// ��ͼ���ߵĽڵ��б�
	vector< MapWalkVertex* > m_MapWalkVertexes ; 
	// ��ͼ���ߵıߵľ���
	vector< Sprite* > m_Lines ; 

	// ͼ�ڵ�ID�����
	unordered_map< string , int > m_VertexIdTable ; 

	// ��ͼ�༭���õ���ʱ����
	struct  EditData
	{
		MapWalkVertex * pMwv ; //��ʼ��

		// �༭�߶�
		Sprite * pSprEdgeLine ; 

		// �϶�ƫ������ drag_content
		Point ptDrag ;
	} m_EditData ;
};


#endif
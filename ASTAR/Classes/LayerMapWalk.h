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
		//  放置顶点
		PutVertex , 
		// 拖曳场景
		DragContent ,
		// 拖曳边
		DragEdge , 
		// 放置角色
		PositionRole , 
		// 行走
		RoleWalk , 
	};

	LayerMapWalk();
	~LayerMapWalk();

	bool onTouchBegan( Touch *touch , Event *unused_event ); 

	void onTouchMoved( Touch *touch , Event *unused_event ); 

	void onTouchEnded( Touch *touch , Event *unused_event );

	// 判断是否命中顶点
	// 返回命中的顶点的指针。没命中，返回0
	MapWalkVertex* HitMapWalkVertex( const Vec2& pos )  ; 

	// 添加一个顶点
	void AddVertex( MapWalkVertex* pMwv , const char * pszId = 0 ) ;
	// 添加一条边
	void AddEdge( MapWalkVertex* pMwv1 , MapWalkVertex* pMwv2 ) ; 

	// 创建一条精灵直线
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

	
	// 地图行走的节点列表
	vector< MapWalkVertex* > m_MapWalkVertexes ; 
	// 地图行走的边的精灵
	vector< Sprite* > m_Lines ; 

	// 图节点ID分配表
	unordered_map< string , int > m_VertexIdTable ; 

	// 地图编辑所用的临时数据
	struct  EditData
	{
		MapWalkVertex * pMwv ; //开始点

		// 编辑线段
		Sprite * pSprEdgeLine ; 

		// 拖动偏移向量 drag_content
		Point ptDrag ;
	} m_EditData ;
};


#endif
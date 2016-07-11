#ifndef _GRAPH_H_
#define _GRAPH_H_
//#include <vector>
#include <unordered_map>
#include <string>//两个string相加需要用这个
using namespace std;

class Vertex;
class Edge;
class Graph;

//===========================================================
/*
	顶点
*/
class Vertex{
	friend class Graph;
public:
	
	Vertex(const string& name){
		m_strId=name;
		m_pGraph=nullptr;
	};

	~Vertex(){};

	// 附加数据
	unordered_map< string , void*> UserData ;

	//getter  setter
	const unordered_map< string , Edge* >& GetEdgesOut( ) const { return m_EdgesOut ; }//得到出边集合

	const unordered_map< string , Edge* >& GetEdgesIn( ) const { return m_EdgesIn ; }//得到入边集合

	const string& GetId( ) const { return m_strId ; }//得到id

	const string& GetText( ) const { return m_Text ; }//得到text
	void SetText( const string& Text ) { m_Text = Text ; }//设置text//set===================================

	Graph * GetGraph( ) { return m_pGraph ; }//得到图

	// 寻路算法需要的数据
	struct Pathfinding
	{
		// 路径代价估计
		int Cost ; 

		// 标识符
		int Flag ;

		// 启发式函数的计算出来的值
		//启发式的
		int Heuristic ; 

		// 顶点的前驱顶点。
		Vertex * pParent ; 

		Pathfinding( )
		{
			Cost = 0 ; 
			Flag = 0 ; 
			Heuristic = 0 ;
			pParent = nullptr ; 
		}
	} PathfindingData ;
protected:
	// 出边集合
	unordered_map< string , Edge* > m_EdgesOut ; //里面放的是这个点的出边和边的另一个点的string 里面的edge都包含这个点 且这个点是start
	// 入边集合
	unordered_map< string , Edge* > m_EdgesIn ;
	// 节点表示的字符串
	string m_Text ; 
	// 节点的ID
	string m_strId ;
	// 用于寻路算法。路径代价估计  
    //int m_Cost ;  
	// 所属的图
	Graph * m_pGraph ; 
};
//===============================================================
/*
	有向边
*/
class Edge{
	friend class Graph;
public:
	Edge(){
		m_Weight=0;
		m_pStartVertex=nullptr;
		m_pEndVertex=nullptr;
	};

	//边的构造函数 就是设置start end点
	Edge(Vertex* pStartVertex , Vertex* pEndVertex , int Weight = 0 ){
		m_Weight=Weight;
		m_pStartVertex=pStartVertex;
		m_pEndVertex=pEndVertex;
	};


	//getter  setter
	int GetWeight( ) const { return m_Weight ; }//得到权值
	void SetWeight( int var ) { m_Weight = var ; }//设置权值

	Vertex* GetStartVertex( ) const { return m_pStartVertex ; }//得到起点

	Vertex* GetEndVertex( ) const { return m_pEndVertex ; }//得到终点

protected:
	// 边的权值
	int m_Weight  ;

	//edge里面包含了start和end点的属性
	// 起点的顶点
	Vertex * m_pStartVertex ;
	// 终点的顶点
	Vertex * m_pEndVertex ;
};


//============================================================
/*
	图.
	图会负责释放顶点和边的内存
*/

class Graph{
public:
	Graph();
	~Graph();

	const unordered_map< string , Vertex* >& GetVertexes( ) const { return m_Vertexes ; }//得到顶点集合

	// 添加一个顶点
	void AddVertex( Vertex* pV ) ;

	// 删除一个顶点
	void DeleleVertex( const string& VertexName ) ;


	// 添加一条边。返回边对象
	Edge* AddEdge( const string& Vertex1Name , const string& Vertex2Name , int Weight = 0 ) ;

	// 删除一条边
	void DeleteEdge( const string& StartVertexName , const string& EndVertexName ) ;

	//string getEdgeKey(Vertex* pV1,Vertex* pV2);
protected:
	
	//k-v  string-对象

	// 顶点的集合
	unordered_map< string , Vertex* > m_Vertexes ; 
	// 边的集合。Key的格式“顶点1name->顶点2name"
	unordered_map< string , Edge* > m_Edges ;

#define GetEdgeKey( pV1 , pV2 )(  pV1->m_strId + "->" + pV2->m_strId ) ;
};


#endif
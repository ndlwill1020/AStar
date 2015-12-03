#ifndef _GRAPH_H_
#define _GRAPH_H_
//#include <vector>
#include <unordered_map>
#include <string>//����string�����Ҫ�����
using namespace std;

class Vertex;
class Edge;
class Graph;

//===========================================================
/*
	����
*/
class Vertex{
	friend class Graph;
public:
	
	Vertex(const string& name){
		m_strId=name;
		m_pGraph=nullptr;
	};

	~Vertex(){};

	// ��������
	unordered_map< string , void*> UserData ;

	//getter  setter
	const unordered_map< string , Edge* >& GetEdgesOut( ) const { return m_EdgesOut ; }//�õ����߼���

	const unordered_map< string , Edge* >& GetEdgesIn( ) const { return m_EdgesIn ; }//�õ���߼���

	const string& GetId( ) const { return m_strId ; }//�õ�id

	const string& GetText( ) const { return m_Text ; }//�õ�text
	void SetText( const string& Text ) { m_Text = Text ; }//����text//set===================================

	Graph * GetGraph( ) { return m_pGraph ; }//�õ�ͼ

	// Ѱ·�㷨��Ҫ������
	struct Pathfinding
	{
		// ·�����۹���
		int Cost ; 

		// ��ʶ��
		int Flag ;

		// ����ʽ�����ļ��������ֵ
		//����ʽ��
		int Heuristic ; 

		// �����ǰ�����㡣
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
	// ���߼���
	unordered_map< string , Edge* > m_EdgesOut ; //����ŵ��������ĳ��ߺͱߵ���һ�����string �����edge����������� ���������start
	// ��߼���
	unordered_map< string , Edge* > m_EdgesIn ;
	// �ڵ��ʾ���ַ���
	string m_Text ; 
	// �ڵ��ID
	string m_strId ;
	// ����Ѱ·�㷨��·�����۹���  
    //int m_Cost ;  
	// ������ͼ
	Graph * m_pGraph ; 
};
//===============================================================
/*
	�����
*/
class Edge{
	friend class Graph;
public:
	Edge(){
		m_Weight=0;
		m_pStartVertex=nullptr;
		m_pEndVertex=nullptr;
	};

	//�ߵĹ��캯�� ��������start end��
	Edge(Vertex* pStartVertex , Vertex* pEndVertex , int Weight = 0 ){
		m_Weight=Weight;
		m_pStartVertex=pStartVertex;
		m_pEndVertex=pEndVertex;
	};


	//getter  setter
	int GetWeight( ) const { return m_Weight ; }//�õ�Ȩֵ
	void SetWeight( int var ) { m_Weight = var ; }//����Ȩֵ

	Vertex* GetStartVertex( ) const { return m_pStartVertex ; }//�õ����

	Vertex* GetEndVertex( ) const { return m_pEndVertex ; }//�õ��յ�

protected:
	// �ߵ�Ȩֵ
	int m_Weight  ;

	//edge���������start��end�������
	// ���Ķ���
	Vertex * m_pStartVertex ;
	// �յ�Ķ���
	Vertex * m_pEndVertex ;
};


//============================================================
/*
	ͼ.
	ͼ�Ḻ���ͷŶ���ͱߵ��ڴ�
*/

class Graph{
public:
	Graph();
	~Graph();

	const unordered_map< string , Vertex* >& GetVertexes( ) const { return m_Vertexes ; }//�õ����㼯��

	// ���һ������
	void AddVertex( Vertex* pV ) ;

	// ɾ��һ������
	void DeleleVertex( const string& VertexName ) ;


	// ���һ���ߡ����ر߶���
	Edge* AddEdge( const string& Vertex1Name , const string& Vertex2Name , int Weight = 0 ) ;

	// ɾ��һ����
	void DeleteEdge( const string& StartVertexName , const string& EndVertexName ) ;

	//string getEdgeKey(Vertex* pV1,Vertex* pV2);
protected:
	
	//k-v  string-����

	// ����ļ���
	unordered_map< string , Vertex* > m_Vertexes ; 
	// �ߵļ��ϡ�Key�ĸ�ʽ������1name->����2name"
	unordered_map< string , Edge* > m_Edges ;

#define GetEdgeKey( pV1 , pV2 )(  pV1->m_strId + "->" + pV2->m_strId ) ;
};


#endif
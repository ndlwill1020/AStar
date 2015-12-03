#include "Dijkstra.h"

Dijkstra::Dijkstra(){

}

Dijkstra::~Dijkstra(){

}

/*
Dijkstra  
{  
    �������е�ͼ����  
        ͼ�����·����ֵ��ʼ��Ϊһ���ܴ��ֵ�����磺0x0FFFFFFF  
        �����еĶ��㶼����һ���б�Q��  
    ��ʼ�����·����ֵ��ʼ��Ϊ0  
    PathTree[��ʼ���� ] = 0 ; // ��ʼ����û�и��ڵ�  
  
    ��� Q�б� ��Ϊ�յĻ� ��һֱ������ѭ��  
    {  
        ��Q�б���ѡ��һ��·����ֵ��С�Ķ���v  
        �Զ���v���еĳ��߽���Relax�ɳڲ���  
    }  
  
}  
*/

//graph����  ��ʼ���key
void  Dijkstra::execute(const Graph& Graph , const string& VetexId ){
	//m_result.PathTree.clear();

	const auto& vertexs = Graph.GetVertexes();// �õ����еĵ�
	Vertex *pVertexStart = vertexs.find( VetexId )->second ; //�ҵ�startVertex

	vector<Vertex*> Q;

	//��ʼ��
	for(auto &it : vertexs){
		it.second->PathfindingData.Cost = 0x0FFFFFFF;
		Q.push_back(it.second);//#####
		pVertexStart->PathfindingData.pParent = nullptr;
	}
	//m_result.PathTree[ pVertexStart ] = nullptr ;	//  ��ʼ�����ǰ������Ϊ��
	pVertexStart->PathfindingData.Cost = 0;
	pVertexStart->PathfindingData.pParent = nullptr;
	//Q.push_back(pVertexStart);
	//pVertexStart->PathfindingData.Flag = true;

	for ( ; Q.size()>0; )
	{
		// ѡ����С·�����ƵĶ���
		Vertex* v = ExtractMin( Q ) ;

		// �����еĳ��߽��С��ɳڡ�
		const auto& EO = v->GetEdgesOut( ) ; 

		for (auto& it : EO)
		{
			//ѭ��~
			Edge* pEdge = it.second;
			Relax(v,pEdge->GetEndVertex(),pEdge->GetWeight());//�ı���һ����Ĵ���
		}
	}
}

//�õ�cost������С�ĵ�
//ÿ��ȡ�õ��cost��С�ĵ� ������ �������Ӽ������Ƴ�
Vertex* Dijkstra::ExtractMin( vector< Vertex* >& Q ){//���������� ���޸�ԭ����ֵ
	Vertex* ret = nullptr;
	ret = Q[0];
	int pos = 0;
	for (int i = 1,size = Q.size(); i < size; i++)
	{
		if(ret->PathfindingData.Cost>Q[i]->PathfindingData.Cost){
			ret = Q[i];
			pos = i;
		}
	}
	Q.erase(Q.begin()+pos);//�Ƴ���С�� 
	return ret;
}

/*
void Relax( ����1������2������1������2���ϵ�Ȩֵ)  
{  
    int n = ����1��·������ + ����1������2���ϵ�Ȩֵ ;   
    ��� n С�ڶ���2��·������  
    {  
        ����2��·������ = n ;   
    }  
}  
*/
//v1->v2  �����Ƕ���1������2�ĳ��� Relaxֻ���ܻ��޸Ķ���2��·������ֵ���������޸Ķ���1��

/*
1.�����ж����·������ֵ���г�ʼ�������綼Ϊ1000��Ȼ���������A��·������ֵΪ0��
����2.��A�����г��߽����ɳڣ�B��·�����ۻᱻ����Ϊ5��C��·�����ۻᱻ����Ϊ1��
����3.��B�����г��߽����ɳڣ�D��·�����ۻᱻ����Ϊ8��
����4.��C�����г��߽����ɳڣ�D��·�����۲��䡣��Ϊ11����8��������Relax ����������ж������� ����Դ���ͼƬ
  Relaxʵ�����ǡ������������յ��ϵĶ����·�����ۣ���·������ֵ���ϱ�С��
  ͨ��ģ������һ�����̣����Ƿ����ҵ���D�����·����·������ֵ8��������û�м�¼�����ӱ�Ȩֵ��·���������߹����ġ�Ҫ��¼·�������ǿ�����һ����ϣӳ������磺unordered_map< Vertex* , Vertex* > PathTree ;
  PathTree[pVertex2] = pVertex1 ; ��ʾ����pVertex1�����ǰ��·��������pVertex2��
  ������ģ������Ĺ��̡��ͻᷢ��PathTree��¼��A�ﵽD�����·������D����Ϊkey����ӳ����鵽B������B����Ϊkey����ӳ����鵽A�����������A��D�����·���ˡ�
  Dijkstra��ʵ����һ����ѡ��������ɳڵ�һ���㷨
*/
void Dijkstra::Relax( Vertex* v1 , Vertex* v2 , int Weight ){
	int n = v1->PathfindingData.Cost + Weight ;
	if ( n < v2->PathfindingData.Cost )
	{
		v2->PathfindingData.Cost = n ;

		m_result.PathTree[ v2 ] = v1 ; //v1->v2  
		v2->PathfindingData.pParent = v1 ; //v2��ǰ������ʽv1  ����ǰ���� 
	}
}//(�������ɳڵ���ǰ�淵�ص���Сcost��� ���ߵ�����end�� ����������Щ���cost Ϊ��һ��ȡ����Сcost����׼��)###


//=========================����####���Ż� һ����Ż�����===============================================
/*
void Dijkstra::Execute( const Graph& Graph , const string& VetexId  )
{
	const auto& Vertexes = Graph.GetVertexes( ) ; 
	Vertex* pVertexStart = Vertexes.find( VetexId )->second ; 
	vector< Vertex* > Q ; 

	// ��ʼ������
	for ( auto& it : Vertexes )
	{
		it.second->PathfindingData.Cost = 0x0FFFFFFF ;
		pVertexStart->PathfindingData.pParent = 0 ;
	}
	// ��ʼ����ʼ����
	pVertexStart->PathfindingData.Cost = 0 ;
	pVertexStart->PathfindingData.pParent = 0 ; 
	// ����ʼ��������б���
	Q.push_back( pVertexStart ) ;#####
	pVertexStart->PathfindingData.Flag = true ; 

	for ( ; Q.size() > 0 ; )
	{
		// ѡ����С·�����ƵĶ���
		auto v = ExtractMin( Q ) ;
		v->PathfindingData.Flag = false ; 

		// �����еĳ��߽��С��ɳڡ�
		const auto& EO = v->GetEdgesOut( ) ; 
		for (  auto& it : EO )
		{
			Edge* pEdge = it.second ; 
			Vertex* pVEnd = pEdge->GetEndVertex( ) ;

			bool bRet = Relax( v , pVEnd , pEdge->GetWeight( ) ) ;
			// ����ɳڳɹ��������б��С�
			if ( bRet && pVEnd->PathfindingData.Flag == false )
			{
				Q.push_back( pVEnd ) ;
				pVEnd->PathfindingData.Flag = true ;
			}
		}
		// end for
	}
	// end for

}

Vertex* Dijkstra::ExtractMin( vector< Vertex* >& Q )
{
	Vertex* Ret = 0 ; 

	Ret = Q[ 0 ] ;
	int pos = 0 ; 
	for ( int i = 1 , size = Q.size( ) ; i < size ; ++i )
	{
		if ( Ret->PathfindingData.Cost > Q[ i ]->PathfindingData.Cost )
		{
			Ret = Q[ i ] ; 
			pos = i ; 
		}
	}

	Q.erase( Q.begin() + pos ) ;

	return Ret ;

}



bool Dijkstra::Relax( Vertex* v1 , Vertex* v2 , int Weight )
{
	int n = v1->PathfindingData.Cost + Weight ;
	if ( n < v2->PathfindingData.Cost )
	{
		v2->PathfindingData.Cost = n ;

		//m_Ret.PathTree[ v2 ] = v1 ; 
		v2->PathfindingData.pParent = v1 ; 

		return true ; 
	}

	return false ; 

}
*/
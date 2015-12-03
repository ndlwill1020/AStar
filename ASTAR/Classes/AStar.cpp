#include "AStar.h"

AStar::AStar(){

}

AStar::~AStar(){

}
/*
����ʽ���������A*Ӧ��������չ�ĸ����㡣����ʽ��������ô�����أ���ʽ��ʾ�ǣ�F = G + H���򵥵�˵�����ǣ���ǰ�����·�����ۣ�G�� + ��ǰ�������Ŀ�궥����ƻ��ѵĴ��ۣ�H��

����Ϊ������������A*�㷨�������Dijkstra������ʽ���ݴ�ѡӵ����С·�����۵Ķ���ĳ�ѡӵ����С��F������ʽ������ֵ���Ķ���ͱ����A*�����ۺ���H��ô����أ�����ȡ���㵽Ŀ�궥��ľ��뼴�ɡ�

2.Dijkstra��Relax�ɳں������ĳ���������ʽ����F��ֵ��������������FֵС���������ԭ�ȵ�Fֵ���͸��¸ö���ĸ��ڵ㡢ʵ��·�����ۡ�Fֵ��

����3.ÿ��ѭ�����ж��£��ҳ�������СFֵ�Ķ����ǲ���Ŀ�궥�㡣�����Ŀ�궥�㣬˵���ҵ���·�����㷨������
*/

/*
AStar( ͼG����ʼ����S��Ŀ�궥��T��  
{  
    �����S����Open����  
  
  
    while( Open��Ϊ�գ�  
    {  
        ��Open����ȡ������ֵF��С�Ķ���v  
        ���v����Open����  
  
        if( v ���� Ŀ�궥��T��  
        {  
            // �ҵ���·��  
            retrun ;   
        }  
  
        foreach( v�����г��ߵ��յ㶥��vEnd )  
        {  
            Relax( v , vEnd , �ߵ�Ȩֵ ��  
            if( Relax�ɳڳɹ� �� ����vEnd����Open���� )  
            {  
                ��vEnd����Open���� ;   
                ���vEnd��Open���� ;   
            }  
        }  
    }  
  
}  
*/
void AStar::execute( const Graph& Graph , const string& VetexId ){
	const auto& Vertexes = Graph.GetVertexes( ) ;
	Vertex* pVertexStart = Vertexes.find( VetexId )->second ;//��ʼ��
	vector< Vertex* > Q ;

	// ��ʼ������
	for ( auto& it : Vertexes )
	{
		Vertex* pV = it.second ; 

		pV->PathfindingData.Cost = 0 ;
		pV->PathfindingData.pParent = nullptr ;
		pV->PathfindingData.Heuristic = 0x0FFFFFFF ;//��ʼ��Ϊһ���ܴ�ܴ����
		pV->PathfindingData.Flag = false ;
	}
	// ��ʼ����ʼ����
	pVertexStart->PathfindingData.pParent = nullptr ;
	pVertexStart->PathfindingData.Cost = 0 ;
	pVertexStart->PathfindingData.Heuristic = estimate( pVertexStart , m_pVTarget ) ;
	// ����ʼ��������б���
	Q.push_back( pVertexStart ) ;
	pVertexStart->PathfindingData.Flag = true ;

	for ( ; Q.size( ) > 0 ; ){
		// ѡ����С·�����ƵĶ���
		auto v = ExtractMin( Q ) ;
		v->PathfindingData.Flag = false ;
		if ( v == m_pVTarget )
		{
			return ; 
		}

		// �����еĳ��߽��С��ɳڡ�
		const auto& EO = v->GetEdgesOut( ) ;
		for ( auto& it : EO )
		{
			Edge* pEdge = it.second ;
			Vertex* pVEnd = pEdge->GetEndVertex( ) ;

			bool bRet = Relax( v , pVEnd , pEdge->GetWeight( ) ) ;
			// ����ɳڳɹ��������б��С�
			if ( bRet && pVEnd->PathfindingData.Flag == false )
			{
				Q.push_back( pVEnd ) ;//�����
				pVEnd->PathfindingData.Flag = true ;

			}
		}

	}

}

Vertex* AStar::ExtractMin( vector< Vertex* >& Q ){
	Vertex* Ret = 0 ;

	Ret = Q[ 0 ] ;
	int pos = 0 ;
	for ( int i = 1 , size = Q.size( ) ; i < size ; ++i )
	{
		if ( Ret->PathfindingData.Heuristic > Q[ i ]->PathfindingData.Heuristic )
		{
			Ret = Q[ i ] ;
			pos = i ;
		}
	}

	Q.erase( Q.begin( ) + pos ) ;

	return Ret ;
}

/*bool Relax( ����from , ����to , ���ϵ�Ȩֵ )  
{  
    // A*����ʽ�������� F = G + H   
    G = ����from��·������ + ���ϵ�Ȩֵ ;   
    H = ����to��Ŀ�궥��T�Ĺ��ƴ��� ;   
    F = G + H ;  
  
    if( F < ����to��F����ֵ��  
    {  
        ��¼to�ĸ�·��Ϊfrom ;   
        ����to��·������ֵ����ΪG ;   
        ����to������ʽ����ֵF����ΪF ;   
          
        return true ;  
    }  
  
    return false ;   
}  */
bool AStar::Relax( Vertex* v1 , Vertex* v2 , int Weight ){
	// �����������ʽ����
	int G = v1->PathfindingData.Cost + Weight ;	// ȡ�ô�V1��V2��ʵ��·������
	int H = estimate(v2,m_pVTarget); // ����V2��Ŀ��ڵ��·������
	int nHeuristic = G + H ;	// ʵ�� + ���� = ����ʽ������ֵ ����v2�� 

	// ����Ӵ�·���ﵽĿ��ᱻ֮ǰ����ĸ��̣��͸���
	if(nHeuristic < v2->PathfindingData.Heuristic){
		v2->PathfindingData.Cost = G;
		v2->PathfindingData.pParent = v1;//###
		v2->PathfindingData.Heuristic = nHeuristic;
		return true;
	}
	return false;
}
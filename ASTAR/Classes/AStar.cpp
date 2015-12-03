#include "AStar.h"

AStar::AStar(){

}

AStar::~AStar(){

}
/*
启发式函数会告诉A*应该优先扩展哪个顶点。启发式函数是怎么回事呢？公式表示是：F = G + H。简单地说，就是：当前顶点的路径代价（G） + 当前顶点距离目标顶点估计花费的代价（H）

就是为了让它更加像A*算法。这里，把Dijkstra的启发式数据从选拥有最小路径代价的顶点改成选拥有最小的F（启发式函数的值）的顶点就变成了A*。估价函数H怎么设计呢？这里取顶点到目标顶点的距离即可。

2.Dijkstra的Relax松弛函数，改成限制启发式函数F的值。如果计算出来的F值小于这个顶点原先的F值，就更新该顶点的父节点、实际路径代价、F值。

　　3.每次循环都判断下，找出来的最小F值的顶点是不是目标顶点。如果是目标顶点，说明找到了路径，算法结束。
*/

/*
AStar( 图G，起始顶点S，目标顶点T）  
{  
    把起点S放入Open表中  
  
  
    while( Open表不为空）  
    {  
        从Open表中取出估价值F最小的顶点v  
        标记v不在Open表中  
  
        if( v 等于 目标顶点T）  
        {  
            // 找到了路径  
            retrun ;   
        }  
  
        foreach( v的所有出边的终点顶点vEnd )  
        {  
            Relax( v , vEnd , 边的权值 ）  
            if( Relax松弛成功 且 顶点vEnd不在Open表中 )  
            {  
                把vEnd放入Open表中 ;   
                标记vEnd在Open表中 ;   
            }  
        }  
    }  
  
}  
*/
void AStar::execute( const Graph& Graph , const string& VetexId ){
	const auto& Vertexes = Graph.GetVertexes( ) ;
	Vertex* pVertexStart = Vertexes.find( VetexId )->second ;//开始点
	vector< Vertex* > Q ;

	// 初始化顶点
	for ( auto& it : Vertexes )
	{
		Vertex* pV = it.second ; 

		pV->PathfindingData.Cost = 0 ;
		pV->PathfindingData.pParent = nullptr ;
		pV->PathfindingData.Heuristic = 0x0FFFFFFF ;//初始化为一个很大很大的数
		pV->PathfindingData.Flag = false ;
	}
	// 初始化起始顶点
	pVertexStart->PathfindingData.pParent = nullptr ;
	pVertexStart->PathfindingData.Cost = 0 ;
	pVertexStart->PathfindingData.Heuristic = estimate( pVertexStart , m_pVTarget ) ;
	// 把起始顶点放入列表中
	Q.push_back( pVertexStart ) ;
	pVertexStart->PathfindingData.Flag = true ;

	for ( ; Q.size( ) > 0 ; ){
		// 选出最小路径估计的顶点
		auto v = ExtractMin( Q ) ;
		v->PathfindingData.Flag = false ;
		if ( v == m_pVTarget )
		{
			return ; 
		}

		// 对所有的出边进行“松弛”
		const auto& EO = v->GetEdgesOut( ) ;
		for ( auto& it : EO )
		{
			Edge* pEdge = it.second ;
			Vertex* pVEnd = pEdge->GetEndVertex( ) ;

			bool bRet = Relax( v , pVEnd , pEdge->GetWeight( ) ) ;
			// 如果松弛成功，加入列表中。
			if ( bRet && pVEnd->PathfindingData.Flag == false )
			{
				Q.push_back( pVEnd ) ;//这个点
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

/*bool Relax( 顶点from , 顶点to , 边上的权值 )  
{  
    // A*启发式函数计算 F = G + H   
    G = 顶点from的路径代价 + 边上的权值 ;   
    H = 顶点to到目标顶点T的估计代价 ;   
    F = G + H ;  
  
    if( F < 顶点to的F估价值）  
    {  
        记录to的父路径为from ;   
        顶点to的路径代价值更新为G ;   
        顶点to的启发式估价值F更新为F ;   
          
        return true ;  
    }  
  
    return false ;   
}  */
bool AStar::Relax( Vertex* v1 , Vertex* v2 , int Weight ){
	// 这里就是启发式函数
	int G = v1->PathfindingData.Cost + Weight ;	// 取得从V1到V2的实际路径代价
	int H = estimate(v2,m_pVTarget); // 估计V2到目标节点的路径代价
	int nHeuristic = G + H ;	// 实际 + 估算 = 启发式函数的值 这是v2的 

	// 如果从此路径达到目标会被之前计算的更短，就更新
	if(nHeuristic < v2->PathfindingData.Heuristic){
		v2->PathfindingData.Cost = G;
		v2->PathfindingData.pParent = v1;//###
		v2->PathfindingData.Heuristic = nHeuristic;
		return true;
	}
	return false;
}
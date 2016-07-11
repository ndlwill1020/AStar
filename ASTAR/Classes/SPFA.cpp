#include "SPFA.h"
#include <queue>
/*
2.1.SPFA算法需要什么
　　SPFA需要用到一个先进先出的队列Q。
　　SPFA需要对图中的所有顶点做一个标示，标示其是否在队列Q中。可以用哈希表做映射，也可以为顶点增加一个字段。后者的实现效率更高。

　　2.2.SPFA是怎样执行的
　　2.2.1 SPFA的初始化
　　SPFA的初始化和Dijkstra类似。
　　先把所有顶点的路径估计值初始化为代价最大值。比如：0x0FFFFFFF。
　　所有顶点都标记为不在队列中。
　　起始顶点放入队列Q中。
　　起始顶点标记在队列中。
　　起始顶点的最短路径估计值置为最小值，比如0。
　　然后下面是一个循环
　　2.2.2 SPFA循环
　　循环结束的条件是队列Q为空。第一次进入循环的时候，只有起始顶点一个元素。
　　每次循环，弹出队列头部的一个顶点。
　　对这个顶点的所有出边进行松弛。如果松弛成功，就是出边终点上对应的那个顶点的路径代价值被改变了，且这个被松弛的顶点不在队列Q中，就把这个被松弛的顶点入队Q。注意，这里顶点入队的条件有2：1.松弛成功。2.且不在队列Q中。
　　当队列Q没有了元素。算法结束。

*/

SPFA::SPFA(){

}

SPFA::~SPFA(){

}

/*
void Spfa( 图G，起始顶点VStart )  
{  
    foreach( 对图G中的所有顶点进行遍历,迭代对象v表示遍历到的每一个顶点对象）  
    {  
        设置顶点v的路径代价估计值为代价最大值，例如：0x0FFFFFFF  
        设置标示顶点v不在队列中  
        顶点v的前驱顶点都为空  
    }  
    起始顶点VStart路径代价估计值为最小值0  
    起始顶点VStart入队Q  
  
    for( 如果队列Q不为空）  
    {  
        队列Q弹出一个队头元素v  
        记录v已经不在队列Q中了  
        for( 遍历从队列Q中弹出的队头顶点v的每一个出边）  
        {  
            u = 边终点上的顶点   
            Relax( v , u，边上的权值）  
            if( Relax松弛成功了 && 顶点u不在队列Q中）  
            {  
                u入队Q  
                记录u在队列中了  
            }  
        }  
    }  
}  
*/

/*
入队，如例：q.push(x); 将x 接到队列的末端。
出队，如例：q.pop(); 弹出队列的第一个元素，注意，并不会返回被弹出元素的值。
访问队首元素，如例：q.front()，即最早被压入队列的元素。
访问队尾元素，如例：q.back()，即最后被压入队列的元素。
判断队列空，如例：q.empty()，当队列空时，返回true。
访问队列中的元素个数，如例：q.size()
*/
void SPFA::execute(const Graph& Graph , const string& VetexId ){
	// 取得图的顶点集合  
    const auto& Vertexes = Graph.GetVertexes( ) ;   
    //  取得起始顶点对象  
    Vertex *pVStart = Vertexes.find( VetexId )->second   ;  
  
    // Spfa算法需要一个队列保存顶点  first-in first-out
    queue< Vertex* > Q ;   

	// 初始化
	for ( auto& it : Vertexes )
	{
		Vertex *pV = it.second ; 

		pV->PathfindingData.Cost = 0x0FFFFFFF ;
		//IsInQueue[ pV ] = false ; 
		pV->PathfindingData.Flag = false ;
		pV->PathfindingData.pParent = nullptr ; // 顶点的父路径都设置为空
	}
	pVStart->PathfindingData.Cost = 0 ;			// 起始顶点的路径代价为0
	pVStart->PathfindingData.Flag = true ;		// 起始顶点在队列中
	//m_Ret.PathTree[ pVStart ] = 0 ;				//  起始顶点的父路径为空
	Q.push( pVStart ) ;									// 起始顶点先入队

	for (;Q.size()>0;)
	{
		auto pStartVertex = Q.front( ) ; 
		Q.pop( ) ;	// 队列弹出一个顶点v

		// 松弛点的所有出边
		const auto& Eo = pStartVertex->GetEdgesOut( ) ;
		for ( auto& it : Eo )
		{
			auto pEdge = it.second ; 
			auto pEndVertex = pEdge->GetEndVertex( ) ;
			bool bRelaxRet = Relax( pStartVertex , pEndVertex , pEdge->GetWeight( ) ) ;
			if(bRelaxRet){
				// 如果对于出边松弛成功，且出边对应的终点顶点不在队列中的话，就插入队尾
				if(pEndVertex->PathfindingData.Flag == false){
					Q.push( pEndVertex ) ;
					pEndVertex->PathfindingData.Flag = true ;//false
				}
			}
		}
	}
}

bool SPFA::Relax( Vertex* pStartVertex , Vertex* pEndVertex , int Weight ){
	int n = pStartVertex->PathfindingData.Cost + Weight;
	if(n<pEndVertex->PathfindingData.Cost){
		// 更新路径代价  
        pEndVertex->PathfindingData.Cost = n ;  
        // 更新路径  
        //m_Ret.PathTree[ pEndVertex ] = pStartVertex ;   
        pEndVertex->PathfindingData.pParent = pStartVertex ; 
		return true;//表示更新了
	}
	return false;
}

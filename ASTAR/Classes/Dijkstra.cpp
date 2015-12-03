#include "Dijkstra.h"

Dijkstra::Dijkstra(){

}

Dijkstra::~Dijkstra(){

}

/*
Dijkstra  
{  
    遍历所有的图顶点  
        图顶点的路径估值初始化为一个很大的值，比如：0x0FFFFFFF  
        把所有的顶点都加入一个列表Q中  
    起始顶点的路径估值初始化为0  
    PathTree[起始顶点 ] = 0 ; // 起始顶点没有父节点  
  
    如果 Q列表 不为空的话 就一直做如下循环  
    {  
        在Q列表中选出一个路径估值最小的顶点v  
        对顶点v所有的出边进行Relax松弛操作  
    }  
  
}  
*/

//graph对象  开始点的key
void  Dijkstra::execute(const Graph& Graph , const string& VetexId ){
	//m_result.PathTree.clear();

	const auto& vertexs = Graph.GetVertexes();// 得到所有的点
	Vertex *pVertexStart = vertexs.find( VetexId )->second ; //找到startVertex

	vector<Vertex*> Q;

	//初始化
	for(auto &it : vertexs){
		it.second->PathfindingData.Cost = 0x0FFFFFFF;
		Q.push_back(it.second);//#####
		pVertexStart->PathfindingData.pParent = nullptr;
	}
	//m_result.PathTree[ pVertexStart ] = nullptr ;	//  起始顶点的前驱顶点为空
	pVertexStart->PathfindingData.Cost = 0;
	pVertexStart->PathfindingData.pParent = nullptr;
	//Q.push_back(pVertexStart);
	//pVertexStart->PathfindingData.Flag = true;

	for ( ; Q.size()>0; )
	{
		// 选出最小路径估计的顶点
		Vertex* v = ExtractMin( Q ) ;

		// 对所有的出边进行“松弛”
		const auto& EO = v->GetEdgesOut( ) ; 

		for (auto& it : EO)
		{
			//循环~
			Edge* pEdge = it.second;
			Relax(v,pEdge->GetEndVertex(),pEdge->GetWeight());//改变另一个点的代价
		}
	}
}

//拿到cost代价最小的点
//每次取得点的cost最小的点 并返回 并把它从集合中移除
Vertex* Dijkstra::ExtractMin( vector< Vertex* >& Q ){//传的是引用 会修改原来的值
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
	Q.erase(Q.begin()+pos);//移除最小的 
	return ret;
}

/*
void Relax( 顶点1，顶点2，顶点1到顶点2边上的权值)  
{  
    int n = 顶点1的路径代价 + 顶点1到顶点2边上的权值 ;   
    如果 n 小于顶点2的路径代价  
    {  
        顶点2的路径代价 = n ;   
    }  
}  
*/
//v1->v2  这里是顶点1到顶点2的出边 Relax只可能会修改顶点2的路径代价值，而不会修改顶点1的

/*
1.对所有顶点的路径代价值进行初始化，比如都为1000。然后设置起点A的路径代价值为0。
　　2.对A的所有出边进行松弛，B的路径代价会被更新为5，C的路径代价会被更新为1。
　　3.对B的所有出边进行松弛，D的路径代价会被更新为8。
　　4.对C的所有出边进行松弛，D的路径代价不变。因为11大于8，不满足Relax 函数里面的判断条件。 看资源里的图片
  Relax实际上是“紧缩”出边终点上的顶点的路径代价，让路径代价值不断变小。
  通过模拟这样一个过程，我们发现找到了D的最短路径的路径代价值8。但我们没有记录这个相加边权值的路径是怎样走过来的。要记录路径，我们可以用一个哈希映射表，比如：unordered_map< Vertex* , Vertex* > PathTree ;
  PathTree[pVertex2] = pVertex1 ; 表示设置pVertex1顶点的前驱路径顶点是pVertex2。
  我们再模拟上面的过程。就会发现PathTree记录了A达到D的最短路径。以D对象为key查找映射表会查到B对象，以B对象为key查找映射表会查到A对象。这个就是A到D的最短路径了。
  Dijkstra其实就是一个挑选顶点出来松弛的一个算法
*/
void Dijkstra::Relax( Vertex* v1 , Vertex* v2 , int Weight ){
	int n = v1->PathfindingData.Cost + Weight ;
	if ( n < v2->PathfindingData.Cost )
	{
		v2->PathfindingData.Cost = n ;

		m_result.PathTree[ v2 ] = v1 ; //v1->v2  
		v2->PathfindingData.pParent = v1 ; //v2的前驱顶点式v1  设置前驱点 
	}
}//(这里是松弛的是前面返回的最小cost点的 出边的所有end点 重新设置这些点的cost 为再一次取得最小cost点作准备)###


//=========================做了####的优化 一点点优化而已===============================================
/*
void Dijkstra::Execute( const Graph& Graph , const string& VetexId  )
{
	const auto& Vertexes = Graph.GetVertexes( ) ; 
	Vertex* pVertexStart = Vertexes.find( VetexId )->second ; 
	vector< Vertex* > Q ; 

	// 初始化顶点
	for ( auto& it : Vertexes )
	{
		it.second->PathfindingData.Cost = 0x0FFFFFFF ;
		pVertexStart->PathfindingData.pParent = 0 ;
	}
	// 初始化起始顶点
	pVertexStart->PathfindingData.Cost = 0 ;
	pVertexStart->PathfindingData.pParent = 0 ; 
	// 把起始顶点放入列表中
	Q.push_back( pVertexStart ) ;#####
	pVertexStart->PathfindingData.Flag = true ; 

	for ( ; Q.size() > 0 ; )
	{
		// 选出最小路径估计的顶点
		auto v = ExtractMin( Q ) ;
		v->PathfindingData.Flag = false ; 

		// 对所有的出边进行“松弛”
		const auto& EO = v->GetEdgesOut( ) ; 
		for (  auto& it : EO )
		{
			Edge* pEdge = it.second ; 
			Vertex* pVEnd = pEdge->GetEndVertex( ) ;

			bool bRet = Relax( v , pVEnd , pEdge->GetWeight( ) ) ;
			// 如果松弛成功，加入列表中。
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
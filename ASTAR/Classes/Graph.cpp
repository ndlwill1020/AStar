#include "Graph.h"

Graph::Graph(){

}

Graph::~Graph(){
	// 释放所有顶点
	for ( auto& kv : m_Vertexes )
	{
		delete kv.second ; 
	}

	// 释放所有的边
	for ( auto& kv : m_Edges )
	{
		delete kv.second ; 
	}
}

	

//已理解
void Graph::AddVertex( Vertex* pV ){
	//if(m_Vertexes.find(pV->GetId())!=m_Vertexes.end){//找到了
	//	// 已经存在相同Key的顶点
	//}

	m_Vertexes[pV->GetId()]=pV;
	pV->m_pGraph=this;
}


/*
// erase examples:
  mymap.erase ( mymap.begin() );      // erasing by iterator
  mymap.erase ("France");             // erasing by key
  mymap.erase ( mymap.find("China"), mymap.end() ); // erasing by range
*/
//先删除与这点有关的边 再删除它
//我觉得还存在bug================================================================================graph的边集合少删了边 这个点的入边集合少释放了内存等等问题
void Graph::DeleleVertex( const string& VertexName ){
	Vertex* pV=m_Vertexes.find(VertexName)->second;//得到key为参数名的Vertex

	// 遍历要删除的节点的出边
	//遍历这个Vertex的出边集合
	for(auto it=pV->m_EdgesOut.begin(),end=pV->m_EdgesOut.end();it!=end;it++){
		Edge* pEdgeOut=it->second;//出边
		// 删除入边记录
		pEdgeOut->m_pEndVertex->m_EdgesIn.erase( VertexName ) ;//另一个点的入边
		// 在边集合列表中删除
		string key=GetEdgeKey(pV,pEdgeOut->m_pEndVertex);
		m_Edges.erase(key);
		// 删除边对象
		delete pEdgeOut;//删除入边的edge就行 因为另一个点的入边也是这条边 是同一块内存 删除一个就行了
	}

	delete pV;

}


//单向的 前者为start点  已理解
//前者加入v1的出边集合 后者加入v2的入边集合
Edge* Graph::AddEdge( const string& Vertex1Name , const string& Vertex2Name , int Weight) {
	Vertex* pV1=m_Vertexes.find(Vertex1Name)->second;//Vertexs集合里找到key为参数的 Vertex
	Vertex* pV2=m_Vertexes.find(Vertex2Name)->second;

	// 加入边集合 加入到graph的edges
	Edge *pEdge = new Edge( pV1 , pV2 , Weight ) ;
	string key=GetEdgeKey(pV1,pV2);//边的key
	m_Edges[key]=pEdge;

	// 加入V1的出边
	pV1->m_EdgesOut[ Vertex2Name ] = pEdge ;//pv1点的出边集合 它的key是边的另一个点的id
	// 加入V2的入边
	pV2->m_EdgesIn[ Vertex1Name ] = pEdge ;


	return pEdge;
}

/*string Graph::getEdgeKey(Vertex* pV1,Vertex* pV2){
	return pV1->m_strId+"->"+pV2->m_strId;
}*/

//这只是单向的 交换两个参数 删除另一条边
void Graph::DeleteEdge( const string& StartVertexName , const string& EndVertexName ){
	Vertex *pV1 = m_Vertexes.find( StartVertexName )->second ;
	Vertex *pV2 = m_Vertexes.find( EndVertexName )->second ;

	string key = GetEdgeKey( pV1 , pV2 ) ;

	Edge *pEdge = m_Edges.find( key )->second ;

	// 在顶点1的出边列表中删除
	pV1->m_EdgesOut.erase( EndVertexName ) ; 
	// 在顶点2的入边列表中删除
	pV2->m_EdgesIn.erase( StartVertexName ) ;

	// 在边集合列表中删除
	m_Edges.erase( key ) ; 

	delete pEdge;
}
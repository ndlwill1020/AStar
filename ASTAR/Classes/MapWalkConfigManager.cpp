#include "MapWalkConfigManager.h"
#include "MapWalkVertex.h"
#include "tinyxml2\tinyxml2.h"


void MapWalkConfigManager::load(const string& ConfigFileName,LayerMapWalk* p_LayerMapWalk){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(ConfigFileName.c_str());
	unordered_map<string,MapWalkVertex*> m_MwvList;//MapVertexs

	auto pElemRoot = doc.RootElement();
	// 读取顶点的信息。创建出相应的顶点在界面上显示
	auto pElemVertexes = pElemRoot->FirstChildElement();
	for (auto pElem = pElemVertexes->FirstChildElement();pElem != nullptr;pElem = pElem->NextSiblingElement())//NextSiblingElement 下个同级元素
	{
		string strId = pElem->Attribute("Id");
		float x = atof( pElem->Attribute( "x" ) ) ; 
		float y = atof( pElem->Attribute( "y" ) ) ;

		auto pMwv = MapWalkVertex::create( ) ; 
		pMwv->setPosition( x , y ) ; 
		p_LayerMapWalk->AddVertex( pMwv , strId.c_str() ) ;

		m_MwvList[ strId ] = pMwv ; 
	}

	// 读取边的信息。创建出相应的边。
	auto pElemEdge = pElemRoot->FirstChildElement( "Edges" ) ;
	for ( auto pElem = pElemEdge->FirstChildElement( ) ; pElem != 0 ; pElem = pElem->NextSiblingElement( ) )
	{
		string v1Id = pElem->Attribute( "StartVertexId" ) ;
		string v2Id = pElem->Attribute( "EndVertexId" ) ;
		int  Weight = atof( pElem->Attribute( "Weight" ) ) ;

		p_LayerMapWalk->AddEdge( m_MwvList[ v1Id ] , m_MwvList[ v2Id ] ) ; 

	}
}

void MapWalkConfigManager::save(const string& ConfigFileName,LayerMapWalk* p_LayerMapWalk){
	tinyxml2::XMLDocument doc ;

	auto pElemGraph= doc.NewElement( "Graph" ) ; 
	doc.InsertEndChild( pElemGraph ) ;

	auto pElemGvRoot = doc.NewElement( "Vertexes" ) ;
	pElemGraph->InsertEndChild( pElemGvRoot ) ;

	// 保存顶点信息
	for ( size_t i = 0 ; i < p_LayerMapWalk->m_MapWalkVertexes.size( ) ; ++i )
	{

		// m_MapWalkVertexes  地图行走的节点列表
		auto pMwv = p_LayerMapWalk->m_MapWalkVertexes[ i ] ;//MapVertex
		auto pElemGv = doc.NewElement( "Vertex" ) ;

		pElemGv->SetAttribute( "Id" , pMwv->GetGraphVertex()->GetId().c_str() ) ;

		pElemGv->SetAttribute( "x" , pMwv->getPositionX( ) ) ;

		pElemGv->SetAttribute( "y" , pMwv->getPositionY( ) ) ;

		pElemGvRoot->InsertEndChild( pElemGv ) ;
	}

	auto pElemEdgeRoot = doc.NewElement( "Edges" ) ;
	pElemGraph->InsertEndChild( pElemEdgeRoot ) ;
	// 保存边的信息
	for ( size_t i = 0 ; i < p_LayerMapWalk->m_MapWalkVertexes.size( ) ; ++i )
	{
		auto pMwvStart = p_LayerMapWalk->m_MapWalkVertexes[ i ] ;

		auto pVS = pMwvStart->GetGraphVertex( ) ; //得到相对应的GraphVertex
		// 遍历所有出边
		const auto& Eo = pVS->GetEdgesOut( ) ;//得到出边集合`得到以pVS作为开始点的线段 
		for ( auto& it : Eo )
		{
			auto pElemEdge = doc.NewElement( "Edge" ) ;

			auto pEdge = it.second ; 
			auto pVE = pEdge->GetEndVertex( ) ;//得到结束点

			pElemEdge->SetAttribute( "StartVertexId" , pVS->GetId( ).c_str() ) ; 
			pElemEdge->SetAttribute( "EndVertexId" , pVE->GetId( ).c_str() ) ;
			pElemEdge->SetAttribute( "Weight" , pEdge->GetWeight() ) ;

			pElemEdgeRoot->InsertEndChild( pElemEdge ) ;
		}
		
	}

	doc.SaveFile( ConfigFileName.c_str() ) ; 
}
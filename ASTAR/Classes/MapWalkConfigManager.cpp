#include "MapWalkConfigManager.h"
#include "MapWalkVertex.h"
#include "tinyxml2\tinyxml2.h"


void MapWalkConfigManager::load(const string& ConfigFileName,LayerMapWalk* p_LayerMapWalk){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(ConfigFileName.c_str());
	unordered_map<string,MapWalkVertex*> m_MwvList;//MapVertexs

	auto pElemRoot = doc.RootElement();
	// ��ȡ�������Ϣ����������Ӧ�Ķ����ڽ�������ʾ
	auto pElemVertexes = pElemRoot->FirstChildElement();
	for (auto pElem = pElemVertexes->FirstChildElement();pElem != nullptr;pElem = pElem->NextSiblingElement())//NextSiblingElement �¸�ͬ��Ԫ��
	{
		string strId = pElem->Attribute("Id");
		float x = atof( pElem->Attribute( "x" ) ) ; 
		float y = atof( pElem->Attribute( "y" ) ) ;

		auto pMwv = MapWalkVertex::create( ) ; 
		pMwv->setPosition( x , y ) ; 
		p_LayerMapWalk->AddVertex( pMwv , strId.c_str() ) ;

		m_MwvList[ strId ] = pMwv ; 
	}

	// ��ȡ�ߵ���Ϣ����������Ӧ�ıߡ�
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

	// ���涥����Ϣ
	for ( size_t i = 0 ; i < p_LayerMapWalk->m_MapWalkVertexes.size( ) ; ++i )
	{

		// m_MapWalkVertexes  ��ͼ���ߵĽڵ��б�
		auto pMwv = p_LayerMapWalk->m_MapWalkVertexes[ i ] ;//MapVertex
		auto pElemGv = doc.NewElement( "Vertex" ) ;

		pElemGv->SetAttribute( "Id" , pMwv->GetGraphVertex()->GetId().c_str() ) ;

		pElemGv->SetAttribute( "x" , pMwv->getPositionX( ) ) ;

		pElemGv->SetAttribute( "y" , pMwv->getPositionY( ) ) ;

		pElemGvRoot->InsertEndChild( pElemGv ) ;
	}

	auto pElemEdgeRoot = doc.NewElement( "Edges" ) ;
	pElemGraph->InsertEndChild( pElemEdgeRoot ) ;
	// ����ߵ���Ϣ
	for ( size_t i = 0 ; i < p_LayerMapWalk->m_MapWalkVertexes.size( ) ; ++i )
	{
		auto pMwvStart = p_LayerMapWalk->m_MapWalkVertexes[ i ] ;

		auto pVS = pMwvStart->GetGraphVertex( ) ; //�õ����Ӧ��GraphVertex
		// �������г���
		const auto& Eo = pVS->GetEdgesOut( ) ;//�õ����߼���`�õ���pVS��Ϊ��ʼ����߶� 
		for ( auto& it : Eo )
		{
			auto pElemEdge = doc.NewElement( "Edge" ) ;

			auto pEdge = it.second ; 
			auto pVE = pEdge->GetEndVertex( ) ;//�õ�������

			pElemEdge->SetAttribute( "StartVertexId" , pVS->GetId( ).c_str() ) ; 
			pElemEdge->SetAttribute( "EndVertexId" , pVE->GetId( ).c_str() ) ;
			pElemEdge->SetAttribute( "Weight" , pEdge->GetWeight() ) ;

			pElemEdgeRoot->InsertEndChild( pElemEdge ) ;
		}
		
	}

	doc.SaveFile( ConfigFileName.c_str() ) ; 
}
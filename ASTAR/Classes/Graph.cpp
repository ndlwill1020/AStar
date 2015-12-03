#include "Graph.h"

Graph::Graph(){

}

Graph::~Graph(){
	// �ͷ����ж���
	for ( auto& kv : m_Vertexes )
	{
		delete kv.second ; 
	}

	// �ͷ����еı�
	for ( auto& kv : m_Edges )
	{
		delete kv.second ; 
	}
}

	

//�����
void Graph::AddVertex( Vertex* pV ){
	//if(m_Vertexes.find(pV->GetId())!=m_Vertexes.end){//�ҵ���
	//	// �Ѿ�������ͬKey�Ķ���
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
//��ɾ��������йصı� ��ɾ����
//�Ҿ��û�����bug================================================================================graph�ı߼�����ɾ�˱� ��������߼������ͷ����ڴ�ȵ�����
void Graph::DeleleVertex( const string& VertexName ){
	Vertex* pV=m_Vertexes.find(VertexName)->second;//�õ�keyΪ��������Vertex

	// ����Ҫɾ���Ľڵ�ĳ���
	//�������Vertex�ĳ��߼���
	for(auto it=pV->m_EdgesOut.begin(),end=pV->m_EdgesOut.end();it!=end;it++){
		Edge* pEdgeOut=it->second;//����
		// ɾ����߼�¼
		pEdgeOut->m_pEndVertex->m_EdgesIn.erase( VertexName ) ;//��һ��������
		// �ڱ߼����б���ɾ��
		string key=GetEdgeKey(pV,pEdgeOut->m_pEndVertex);
		m_Edges.erase(key);
		// ɾ���߶���
		delete pEdgeOut;//ɾ����ߵ�edge���� ��Ϊ��һ��������Ҳ�������� ��ͬһ���ڴ� ɾ��һ��������
	}

	delete pV;

}


//����� ǰ��Ϊstart��  �����
//ǰ�߼���v1�ĳ��߼��� ���߼���v2����߼���
Edge* Graph::AddEdge( const string& Vertex1Name , const string& Vertex2Name , int Weight) {
	Vertex* pV1=m_Vertexes.find(Vertex1Name)->second;//Vertexs�������ҵ�keyΪ������ Vertex
	Vertex* pV2=m_Vertexes.find(Vertex2Name)->second;

	// ����߼��� ���뵽graph��edges
	Edge *pEdge = new Edge( pV1 , pV2 , Weight ) ;
	string key=GetEdgeKey(pV1,pV2);//�ߵ�key
	m_Edges[key]=pEdge;

	// ����V1�ĳ���
	pV1->m_EdgesOut[ Vertex2Name ] = pEdge ;//pv1��ĳ��߼��� ����key�Ǳߵ���һ�����id
	// ����V2�����
	pV2->m_EdgesIn[ Vertex1Name ] = pEdge ;


	return pEdge;
}

/*string Graph::getEdgeKey(Vertex* pV1,Vertex* pV2){
	return pV1->m_strId+"->"+pV2->m_strId;
}*/

//��ֻ�ǵ���� ������������ ɾ����һ����
void Graph::DeleteEdge( const string& StartVertexName , const string& EndVertexName ){
	Vertex *pV1 = m_Vertexes.find( StartVertexName )->second ;
	Vertex *pV2 = m_Vertexes.find( EndVertexName )->second ;

	string key = GetEdgeKey( pV1 , pV2 ) ;

	Edge *pEdge = m_Edges.find( key )->second ;

	// �ڶ���1�ĳ����б���ɾ��
	pV1->m_EdgesOut.erase( EndVertexName ) ; 
	// �ڶ���2������б���ɾ��
	pV2->m_EdgesIn.erase( StartVertexName ) ;

	// �ڱ߼����б���ɾ��
	m_Edges.erase( key ) ; 

	delete pEdge;
}
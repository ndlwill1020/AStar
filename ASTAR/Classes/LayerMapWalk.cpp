#include "LayerMapWalk.h"
#include "MapWalkVertex.h"
#include "LayerHudControl.h"
#include "Dijkstra.h"
#include "SPFA.h"
#include "AStar.h"

#define ZOrderLine -1 
#define ZOrderVertex 2 
#define ZOrderRole  3 

LayerMapWalk::LayerMapWalk(){
	m_pGraph=nullptr;
}

LayerMapWalk::~LayerMapWalk(){
	if(m_pGraph){
		delete m_pGraph;
	}

}

bool LayerMapWalk::init(){
	if(!Layer::init()){
		return false;	
	}

	
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);

	m_Mode=OperationMode::PutVertex;

	// ��ʼ���༭���� struct
	auto pSprEdgeEditLine = Sprite::create( "line.png" )  ;
	m_EditData.pSprEdgeLine=pSprEdgeEditLine;

	this->addChild(pSprEdgeEditLine);//��ֹ�Զ��ͷ�
	pSprEdgeEditLine->setVisible(false);
	pSprEdgeEditLine->setAnchorPoint(Vec2(0.0f,0.5f));//���� 

	// ��ʼ����ɫ
	m_pRole = Role::create( ) ;
	m_pRole->setPosition( 100 , 100 ) ; 
	m_pRole->setLocalZOrder(ZOrderRole);
	this->addChild( m_pRole ) ;
	m_pRole->setVisible( false ) ; 

	// ��ʼ��ID�����
	//unordered_map< string , int >
	for (int i = 0; i < 1000; i++)
	{
		char sz[100];
		sprintf(sz,"%d",i);
		m_VertexIdTable[sz]=0;
	}

	m_pGraph=new Graph();


	//Vec2 p=Vec2(300,400);
	//log("temp:!!!!%f",p.getLength());�õ��㵽ԭ��ľ���

	return true;
}

bool LayerMapWalk::onTouchBegan( Touch *touch , Event *unused_event ){
	cocos2d::log("touch begin");
	//log("%f:%f================",this->getPositionX(),this->getPositionY());
	auto pos=touch->getLocation();
	cocos2d::log("pos_one:%f:%f",pos.x,pos.y);

	//MapWalkVertex* p_mwv=nullptr;
	
	switch (m_Mode)
	{
	case LayerMapWalk::OperationMode::PutVertex:
		{
		cocos2d::log("put vertex");
		// ����任
		pos = this->convertToNodeSpace( pos ) ;//(0,0)���е�
		cocos2d::log("pos_two:%f:%f",pos.x,pos.y);

		MapWalkVertex* p_mwv=HitMapWalkVertex(pos);
		//p_mwv=HitMapWalkVertex(pos);

		if ( p_mwv )
		{
			m_Mode = OperationMode::DragEdge ;
			auto pSprLine = m_EditData.pSprEdgeLine ; 
			pSprLine->setPosition( pos ) ;
			pSprLine->setVisible( true ) ;

			MakeLine( pSprLine , pSprLine->getPosition( ) , pos ) ;

			m_EditData.pMwv = p_mwv ; 
		}
		else
		{
			// ������ͼ���ߵĶ���
			log("here=============");
			auto pMwv = MapWalkVertex::create( ) ;//MapVertex
			pMwv->setPosition( pos ) ;
			AddVertex( pMwv ) ; 

		}
		
		}
		break;
	case LayerMapWalk::OperationMode::DragContent:
		{
		cocos2d::log("drag content");
		m_EditData.ptDrag = pos-this->getPosition();
		}
		break;
	case OperationMode::PositionRole:
	{
		//// ����任
		pos = this->convertToNodeSpace( pos ) ;

		auto pMwv = HitMapWalkVertex( pos ) ;
		if ( pMwv )
		{
			
			m_pRole->setPosition( pMwv->getPosition( ) ) ; 
			m_pRole->setVisible( true ) ; 
			m_pRole->UserData[ "StartVertex" ] = pMwv ; 
		}
	}
	break;
	/*case LayerMapWalk::OperationMode::DragEdge:
		break;
	case LayerMapWalk::OperationMode::PositionRole:
		break;
	*/case LayerMapWalk::OperationMode::RoleWalk:
	{
		pos = this->convertToNodeSpace(pos);
		auto pMwv = HitMapWalkVertex(pos);
		if(pMwv){
			auto pVertex = pMwv->GetGraphVertex();//����ĵ�����Ӧ��Vertex  �յ� target
			 
			// ���
			MapWalkVertex* pMwvStart = ( MapWalkVertex*)m_pRole->UserData["StartVertex"];

			int nTimeStart ; 
			int Elapsed ; 
			char sz[ 256 ] ; 
			string strElapseds ; 

			// �������·������Dijkstra
			/*nTimeStart = ::clock();//clock()
			Dijkstra dijkstra;
			dijkstra.execute(*m_pGraph,pMwvStart->GetGraphVertex()->GetId());//��ʼ���id
			Elapsed = ::clock()-nTimeStart;
			sprintf( sz , "Dijkstra : %d ms \n" , Elapsed ) ; 
			strElapseds += sz ; */

			
			// �� Spfa
			/*nTimeStart = ::clock( ) ;
			SPFA spfa; 
			spfa.execute( *m_pGraph , pMwvStart->GetGraphVertex( )->GetId( ) ) ; 
			Elapsed = ::clock( ) - nTimeStart ;
			sprintf( sz , "Spfa : %d ms \n" , Elapsed ) ;
			strElapseds += sz ;*/
			
			//��AStar
			nTimeStart = ::clock( ) ;

			// A*�ģȹ��ۺ���  ����������ľ��볤��
			auto Estimate = [ ]( const Vertex* pVCurrent , const Vertex* pVTarget )->int
			{
				MapWalkVertex * pMwv1 = ( MapWalkVertex* )pVCurrent->UserData.find( "mwv" )->second ;
				MapWalkVertex * pMwv2 = ( MapWalkVertex* )pVTarget->UserData.find( "mwv" )->second ;
				Point v = pMwv1->getPosition( ) - pMwv2->getPosition( ) ; 
				int H = v.getLength( ) ; 
				return H ; 

			} ; 

			AStar aStar;
			// ����Ŀ�Ķ���
			aStar.SetTarget( pVertex ) ;	
			// ���ãȹ��ۺ���
			aStar.estimate = Estimate ; 
			// ��ʼִ��
			aStar.execute( *m_pGraph , pMwvStart->GetGraphVertex( )->GetId( ) ) ; 

			Elapsed = ::clock( ) - nTimeStart ;
			sprintf( sz , "AStar : %d ms \n" , Elapsed ) ;
			strElapseds += sz ;
			
			m_LayerHudControl->m_pTxtInfo2->setString( strElapseds ) ;

			// ȡ��·������ MapWalkVertex
			vector< MapWalkVertex* > MwvSeq ; 
			MwvSeq.push_back(pMwv);

			for (Vertex* pParent = pVertex->PathfindingData.pParent;pParent!=nullptr;pParent = pParent->PathfindingData.pParent)
			{
				MwvSeq.push_back((MapWalkVertex*)pParent->UserData["mwv"]);
			}

			// ��ʼ���߶���
			StartWalk( MwvSeq ) ; 
		}
	}
	break;
	default:
		{
		
		}
		break;
	}
	return true;
}

void LayerMapWalk::StartWalk( const vector< MapWalkVertex* >& GvSeq ){
	Action *pAct = m_pRole->getActionByTag( 1 ) ; 
	if ( pAct != nullptr && pAct->isDone() == false )
	{
		return ; 
	}

	Vector<FiniteTimeAction*> Actions;
	for (int i = GvSeq.size()-2; i >=0; i--)//iԽ�� ��ʾԽǰ��  
	{
		// ����ÿһ�εľ���
		Point v = GvSeq[ i ]->getPosition( ) - GvSeq[ i + 1 ]->getPosition( ) ; 
		float len = v.getLength( ) ; 
		float duration = len / 100 * 1.2 ; 

		Role::State Direction;
		float rad = v.getAngle( Point( 1 , 1 ) ) ; 
		float Degree = CC_RADIANS_TO_DEGREES( rad ) ; 
		if ( Degree >= 0 && Degree < 90 )
		{
			Direction = Role::State::WalkRight ; 
		}
		else if ( Degree >= 90 && Degree <= 180 )
		{
			Direction = Role::State::WalkBottom ;
		}
		else if ( Degree < 0 && Degree >= -90 )
		{
			Direction = Role::State::WalkTop ;
		}
		else if ( Degree < -90 && Degree >= -180 )
		{
			Direction = Role::State::WalkLeft ;
		}

		auto fnSetDirection = [ ]( Role *pRole , Role::State Dir )
		{
			pRole->setState( Dir ) ; 
		} ; 
		Actions.pushBack( CallFunc::create( bind( fnSetDirection , m_pRole , Direction ) ) ) ;//�ȸı�״̬

		FiniteTimeAction *pAct = MoveTo::create( duration , GvSeq[ i ]->getPosition( ) ) ;
		auto fn = [ ]( Role *pRole , MapWalkVertex * pGv )
		{
			pRole->UserData[ "StartVertex" ] = pGv ; 
		} ; 
		Actions.pushBack( pAct ) ;//Ȼ���ƶ�
		Actions.pushBack( CallFunc::create( bind( fn , m_pRole , GvSeq[ i ] ) ) ) ;//Ȼ������role��ʼ��
	}

		auto fnStopActions = [ ]( Role *pRole )
	{
		pRole->setState(  Role::State::None ) ;
	} ; 
	Actions.pushBack( CallFunc::create( bind( fnStopActions , m_pRole ) ) ) ;//���ֹͣ


	if ( Actions.size( ) == 0 )
	{
		return ; 
	}

	auto pSeq = Sequence::create( Actions ) ;
	pSeq->setTag( 1 ) ; 
	m_pRole->runAction( pSeq ) ; 
}

MapWalkVertex* LayerMapWalk::HitMapWalkVertex( const Vec2& pos ){
	cocos2d::log("hit function");

	MapWalkVertex* pRet=nullptr;//node���������
	// �Ƿ����нڵ�  (vertex��ͼ�εĴ�СΪ80,50)
	for(auto &it : m_MapWalkVertexes){
		log("not null==================");
		auto v=pos-it->getPosition();
		if(v.getLengthSq()<50*50){
			pRet=it;
			break;
		}
	}
	return pRet;
}

//MapVertex  Vertex�໥��
void LayerMapWalk::AddVertex( MapWalkVertex* pMwv , const char * pszId){
	//pMwv�Ǹ�node
	this->addChild(pMwv);
	m_MapWalkVertexes.push_back(pMwv);
	// ��ȡ����ID
	string strId ;

	if(pszId==0){
		cocos2d::log("id is 0");
		auto it = m_VertexIdTable.begin( ) ; //map������� 
		strId = it->first ;
		log("%s",strId.c_str());
		m_VertexIdTable.erase( it ) ; 
	}else{
		auto it = m_VertexIdTable.find( pszId ) ; 
		if ( it != m_VertexIdTable.end( ) )
		{
			m_VertexIdTable.erase( it ) ; 
			strId = pszId ; 
		}
	}

	//  ����ͼ����
	Vertex *pGv = new Vertex( strId ) ;
	m_pGraph->AddVertex( pGv ) ;//graph add vertex ���뵽graph�ĵ㼯��
	//  ��ͼ���ߵĶ����ͼ����
	pMwv->SetGraphVertex( pGv ) ;
	// ͼ����󶨵�ͼ���ߵĶ���
	pGv->UserData[ "mwv" ] = pMwv  ;

	//pMwv�Ǹ�node
	// ����ľ����ʾ
	auto pSpr = Sprite::create( "vertex_1.png" ) ;
	pMwv->addChild( pSpr ) ;


	
}

// ���һ����
//��ʾ��MapEdgeΪ1��sprite (GraphEdgeΪ2�� ���ص���)
void LayerMapWalk::AddEdge( MapWalkVertex* pMwv1 , MapWalkVertex* pMwv2 ){
	// ���ظ����
	auto pGv1 = pMwv1->GetGraphVertex( ) ; 
	auto pGv2 = pMwv2->GetGraphVertex( ) ;//�õ�Vertex
	const auto& eo1 = pGv1->GetEdgesOut( ) ; //�õ����߼���
	const auto& eo2 = pGv2->GetEdgesOut( ) ;

	if(eo1.find(pGv2->GetId())!=eo1.end() || eo2.find(pGv1->GetId())!=eo2.end()){//��ʾ�ҵ��� ��ʾ�Ѿ������߶�
		return;
	}

	//�������ʾ�߶λ�û���� ��û����
	float Distance = ( pMwv1->getPosition( ) - pMwv2->getPosition( ) ).getLength( ) ;//�õ�����  ����Ȩֵ

	// ���һ����
	//��edge���뵽graph�ı߼��� �ڲ�����vertex���� 
	m_pGraph->AddEdge( pMwv1->GetGraphVertex( )->GetId( ) ,
		pMwv2->GetGraphVertex( )->GetId( ) ,
		Distance
		) ;
	// ��Ϊ������ߣ����ԣ�����Ҳ���һ����
	m_pGraph->AddEdge( pMwv2->GetGraphVertex( )->GetId( ) ,
		pMwv1->GetGraphVertex( )->GetId( ) ,
		Distance
		) ;



	// ��ӱߵı�ʾ��һ������ֱ��
	auto pSprLine = Sprite::create( "line.png" ) ;
	pSprLine->setOpacity( 255 * 0.7 ) ;
	//pSprLine->setColor( Color3B( 0 , 0 , 255 ) ) ;
	MakeLine( pSprLine , pMwv1->getPosition( ) , pMwv2->getPosition( ) ) ;
	this->addChild( pSprLine , ZOrderLine ) ;
	m_Lines.push_back( pSprLine ) ;
}


void LayerMapWalk::MakeLine( Sprite* pSpr , const Point& pt1 , const Point& pt2 ){
	// ����ê����λ��
	pSpr->setAnchorPoint( Point( 0 , 0.5 ) ) ;
	pSpr->setPosition( pt1 ) ;

	//lineͼ�� (10,5)
	//����
	float width=pSpr->getTexture()->getContentSize().width;
	log("width:%f",width);
	float width1=pSpr->getContentSize().width;
	log("width1:%f",width1);

	auto v=pt2-pt1;
	float len=v.getLength();
	float scaleX=len/width;
	pSpr->setScaleX(scaleX);

	//��ת
	float rad=v.getAngle();
	float rotation=CC_RADIANS_TO_DEGREES(-rad);
	log("ratation:%f",rotation);
	float rotation1=-1*CC_RADIANS_TO_DEGREES(rad);
	log("ratation1:%f",rotation1);
	pSpr->setRotation(rotation);


	
}

void LayerMapWalk::onTouchMoved( Touch *touch , Event *unused_event ){
	auto pos = touch->getLocation( ) ; 

	switch ( m_Mode )
	{

	case OperationMode::DragEdge:
	{
		// ����任
		pos = this->convertToNodeSpace( pos ) ; 

		auto pSprLine = m_EditData.pSprEdgeLine ; 
		MakeLine( pSprLine , pSprLine->getPosition( ) , pos ) ; 
		
	}
	break;

	case OperationMode::DragContent:
	{
		Point pt = pos - m_EditData.ptDrag ; 
		this->setPosition( pt ) ; 
	}
	break;

	}
}

void LayerMapWalk::onTouchEnded( Touch *touch , Event *unused_event ){
	// ����任
	auto pos = this->convertTouchToNodeSpace( touch ) ;

	switch ( m_Mode )
	{
	case OperationMode::DragEdge:
	{
		auto pMwv = HitMapWalkVertex( pos ) ;
		if ( pMwv )
		{
			AddEdge( m_EditData.pMwv , pMwv ) ; 

			m_EditData.pSprEdgeLine->setVisible( false ) ; //m_EditData�Ǹ���ʱ���� 

			m_Mode = OperationMode::PutVertex ; 
		}
		else
		{
			m_EditData.pSprEdgeLine->setVisible( false ) ;

			m_Mode = OperationMode::PutVertex ;
		}
	}
	break;

	}
}
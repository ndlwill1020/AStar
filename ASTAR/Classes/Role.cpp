#include "Role.h"

Role::Role(){
	m_state=State::None;
}

Role::~Role(){

}

bool Role::init(){
	if(!Node::init()){
		return false;
	}
	auto pTex=TextureCache::getInstance()->addImage("kaito.png");
	m_size.width=pTex->getContentSize().width/4;
	m_size.height=pTex->getContentSize().height/4;

	m_pSprMain=Sprite::create("kaito.png",Rect(m_size.width*0,m_size.height*2,m_size.width,m_size.height));
	this->addChild(m_pSprMain);
	m_pSprMain->setAnchorPoint(Vec2(0.5f,0.0f));
	//m_pSprMain->setAnchorPoint(Vec2(0.5f,0.5f));//0.5,0.05

	createActions();
	setState( State::WalkBottom ) ; 
	setState( State::None ) ;
	
	return true;
}
	

void Role::setState(State type){
	m_pSprMain->stopAllActions();
	switch (type)
	{
	case Role::State::None:
		//之前的状态
		switch (m_state)
		{
		case Role::State::None:

			break;
		case Role::State::WalkLeft:
			m_pSprMain->setTextureRect(Rect(m_size.width*0,m_size.height*1,m_size.width,m_size.height));
			break;
		case Role::State::WalkRight:
			m_pSprMain->setTextureRect( Rect( m_size.width * 0 , m_size.height * 2 , m_size.width , m_size.height ) ) ;
			break;
		case Role::State::WalkTop:
			m_pSprMain->setTextureRect( Rect( m_size.width * 0 , m_size.height * 3 , m_size.width , m_size.height ) ) ;
			break;
		case Role::State::WalkBottom:
			m_pSprMain->setTextureRect( Rect( m_size.width * 0 , m_size.height * 0 , m_size.width , m_size.height ) );
			break;
		default:
			break;
		}
		break;
	case Role::State::WalkLeft:
		m_pSprMain->runAction(m_pActWalkLeft);
		break;
	case Role::State::WalkRight:
		m_pSprMain->runAction(m_pActWalkRight);
		break;
	case Role::State::WalkTop:
		//m_pSprMain->setTextureRect( Rect( m_size.width * 0 , m_size.height * 0 , m_size.width , m_size.height ) );
		m_pSprMain->runAction( m_pActWalkTop ) ;
		break;
	case Role::State::WalkBottom:
		m_pSprMain->runAction(m_pActWalkBottom);
		break;
	default:
		break;
	}
	m_state=type;
}

void Role::createActions(){
	//top-bottom截图
	auto pTex=TextureCache::getInstance()->addImage("kaito.png");//得到texture2d 
	float delayPerUnit=0.15;

	//右
	auto pAnim=Animation::create();
	pAnim->setDelayPerUnit(delayPerUnit);
	for(int i=0;i<4;i++){
		Rect rect(m_size.width*i,m_size.height*2,m_size.width,m_size.height);
		pAnim->addSpriteFrameWithTexture(pTex,rect);
	}
	m_pActWalkRight=RepeatForever::create(Animate::create(pAnim));
	m_Actions.pushBack(m_pActWalkRight);//把action添加到集合
	//左
	pAnim=Animation::create();
	pAnim->setDelayPerUnit(delayPerUnit);
	for(int i=0;i<4;i++){
		Rect rect(m_size.width*i,m_size.height*1,m_size.width,m_size.height);
		pAnim->addSpriteFrameWithTexture(pTex,rect);
	}
	m_pActWalkLeft=RepeatForever::create(Animate::create(pAnim));
	m_Actions.pushBack(m_pActWalkLeft);
	//下
	pAnim = Animation::create( ) ;
	pAnim->setDelayPerUnit( delayPerUnit ) ;
	for ( int i = 0 ; i < 4 ; ++i )
	{
		Rect rect( m_size.width * i , m_size.height * 0 , m_size.width , m_size.height ) ;
		pAnim->addSpriteFrameWithTexture( pTex , rect ) ;
	}
	m_pActWalkBottom = RepeatForever::create( Animate::create( pAnim ) ) ;
	m_Actions.pushBack( m_pActWalkBottom ) ;
	//上
	pAnim = Animation::create( ) ;
	pAnim->setDelayPerUnit( delayPerUnit ) ;
	for ( int i = 0 ; i < 4 ; ++i )
	{
		Rect rect( m_size.width * i , m_size.height * 3 , m_size.width , m_size.height ) ;
		pAnim->addSpriteFrameWithTexture( pTex , rect ) ;
	}
	m_pActWalkTop = RepeatForever::create( Animate::create( pAnim ) ) ;
	m_Actions.pushBack( m_pActWalkTop ) ;


}
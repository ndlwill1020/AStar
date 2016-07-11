#include "LayerHudControl.h"
#include "MapWalkVertex.h"
#include "MapWalkConfigManager.h"
#include "tinyxml2\tinyxml2.h"
LayerHudControl::LayerHudControl(){
	p_LayerMapWalk = nullptr;
}

LayerHudControl::~LayerHudControl(){


}

bool LayerHudControl::init(){
	if(!Layer::init()){
		return false;
	}

	ui::Widget* p_ui=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/hud_control/hud_control.ExportJson");
	this->addChild(p_ui);
	p_ui->setAnchorPoint(Vec2(0,1));

	auto rect=Director::getInstance()->getVisibleSize();
	p_ui->setPositionY(rect.height);

	m_pTxtInfo=(Text*)ui::Helper::seekWidgetByName(p_ui,"lblInfo");
	m_pTxtInfo2 = ( Text* ) Helper::seekWidgetByName( p_ui , "txtInfo2" ) ;
	/*
	<kv>
    <string Key="btnDrag" Value="mode:drag" />
    <string Key="btnEditGraph" Value="mode:edit" />
    <string Key="btnPositionRole" Value="mode:role" />
    <string Key="btnWalk" Value="mode:walk" />
	</kv>
	*/
	// 读入字符串表
	tinyxml2::XMLDocument doc;
	doc.LoadFile( "config/strings.xml" ) ; 
	auto pRoot=doc.RootElement();
	for (auto pEle=pRoot->FirstChildElement();pEle!=0;pEle=pEle->NextSiblingElement())
	{
		m_StringList[pEle->Attribute("Key")]=pEle->Attribute("Value");
	}
	// 默认是图编辑模式
	m_pTxtInfo->setString(m_StringList["btnEditGraph"]);

	// 静态函数对象。这样对象才不会被销毁。
	static auto fnSetInfo=[&](Widget* pWidget){
		string name=pWidget->getName();
		auto it=m_StringList.find(name);
		if(it!=m_StringList.end()){
			m_pTxtInfo->setString(it->second);
		}
	};

	ui::Button* p_btn;
	function<void(Ref*,Widget::TouchEventType)> fn;

	// 拖曳按钮
	p_btn=(Button*)ui::Helper::seekWidgetByName(p_ui , "btnDrag");
	fn=[&](Ref* pSender,Widget::TouchEventType type){
		if(type==Widget::TouchEventType::ENDED){
			p_LayerMapWalk->m_Mode=LayerMapWalk::OperationMode::DragContent;
			//m_pTxtInfo->setString("mode:drag!");
			fnSetInfo((Widget*)pSender);
		}
	};
	p_btn->addTouchEventListener(fn);


	// 图编辑按钮
	p_btn = ( Button* )Helper::seekWidgetByName( p_ui , "btnEditGraph" ) ;
	fn = [ &]( Ref* pSender , Widget::TouchEventType e )
	{
		if ( e != Widget::TouchEventType::ENDED )	return ;

		p_LayerMapWalk->m_Mode = LayerMapWalk::OperationMode::PutVertex ;
		m_pTxtInfo->setString( "mode:edit!" ) ;
		//fnSetInfo( ( Widget* ) pSender ) ;
	} ;
	p_btn->addTouchEventListener( fn ) ;


	//显示 隐藏图=================================================================
	p_btn = ( Button* ) Helper::seekWidgetByName( p_ui , "btnShowHideGraph" ) ;
	fn = [ &]( Ref* , Widget::TouchEventType e )
	{
		if ( e != Widget::TouchEventType::ENDED )	return ;

		for(auto& it : p_LayerMapWalk->m_MapWalkVertexes){
			it->setVisible(!it->isVisible());
		}
		
		for ( auto& it : p_LayerMapWalk->m_Lines )
		{
			it->setVisible( !it->isVisible( ) ) ;
		}
	} ;
	p_btn->addTouchEventListener( fn ) ;


	// 放置人物
	p_btn = ( Button* ) Helper::seekWidgetByName( p_ui , "btnPositionRole" ) ;
	fn = [ &]( Ref* pSender , Widget::TouchEventType e )
	{
		if ( e != Widget::TouchEventType::ENDED )	return ;

		p_LayerMapWalk->m_Mode = LayerMapWalk::OperationMode::PositionRole ;

		fnSetInfo( ( Widget* ) pSender ) ;
	} ;
	p_btn->addTouchEventListener( fn ) ;


	// 行走
	p_btn = ( Button* ) Helper::seekWidgetByName( p_ui , "btnWalk" ) ;
	fn = [ &]( Ref* pSender , Widget::TouchEventType e )
	{
		if ( e != Widget::TouchEventType::ENDED )	return ;

		p_LayerMapWalk->m_Mode = LayerMapWalk::OperationMode::RoleWalk ;

		fnSetInfo( ( Widget* ) pSender ) ;
	} ;
	p_btn->addTouchEventListener( fn ) ;


	p_btn = ( Button* ) Helper::seekWidgetByName( p_ui , "btnSave" ) ;
	fn = [ &]( Ref* , Widget::TouchEventType e )
	{
		if ( e != Widget::TouchEventType::ENDED )	return ;

		MapWalkConfigManager::save( "config/map_walk.xml" , p_LayerMapWalk ) ; 
	} ;
	p_btn->addTouchEventListener( fn ) ;
	
	
	p_btn = ( Button* ) Helper::seekWidgetByName( p_ui , "btnLoad" ) ;
	fn = [ &]( Ref* , Widget::TouchEventType e )
	{
		if ( e != Widget::TouchEventType::ENDED )	return ;

		MapWalkConfigManager::load( "config/map_walk.xml" , p_LayerMapWalk ) ;
	} ;
	p_btn->addTouchEventListener( fn ) ;

	return true;
}
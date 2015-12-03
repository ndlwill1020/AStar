#include "SceneMapWalk.h"
#include "LayerHudControl.h"

bool SceneMapWalk::init(){
	if(!Scene::init()){
		return false;
	}

	p_LayerMapWalk=LayerMapWalk::create();
	//log("LayerMapWalk->size:%f:%f",p_LayerMapWalk->getContentSize().width,p_LayerMapWalk->getContentSize().height);
	this->addChild(p_LayerMapWalk);

	auto p_LayerHudControl=LayerHudControl::create();
	//log("LayerHudControl->size:%f:%f",p_LayerHudControl->getContentSize().width,p_LayerHudControl->getContentSize().height);
	this->addChild(p_LayerHudControl);

	p_LayerHudControl->p_LayerMapWalk=p_LayerMapWalk;
	p_LayerMapWalk->m_LayerHudControl=p_LayerHudControl;
	return true;
}
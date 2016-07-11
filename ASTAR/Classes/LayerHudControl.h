#ifndef _LAYER_HUD_CONTROL_H_
#define _LAYER_HUD_CONTROL_H_
#include "cocos2d.h"
#include "LayerMapWalk.h"
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "ui\CocosGUI.h"
using namespace cocos2d::ui;

#include <unordered_map>
using namespace std;
USING_NS_CC;

class LayerMapWalk;

class LayerHudControl : public Layer{
public:
	LayerHudControl();
	~LayerHudControl();

	

	bool init();
	CREATE_FUNC(LayerHudControl);
public:
	LayerMapWalk* p_LayerMapWalk;
	Text *m_pTxtInfo ;

	Text *m_pTxtInfo2 ;
private:
	

	

	// 字符串表
	unordered_map< string , string> m_StringList ;
};

#endif
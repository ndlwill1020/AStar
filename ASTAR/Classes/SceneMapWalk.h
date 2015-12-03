#ifndef _SCENE_MAP_WALK_H_
#define _SCENE_MAP_WALK_H_
#include "cocos2d.h"
#include "LayerMapWalk.h"
USING_NS_CC;



class SceneMapWalk : public Scene{
public:
	bool init();
	CREATE_FUNC(SceneMapWalk);
private:
	LayerMapWalk* p_LayerMapWalk;
};

#endif
#ifndef _MAP_WALK_CONFIG_MANAGER_H_
#define _AMP_WALK_CONFIG_MANAGER_H_
#include <string>
#include "LayerMapWalk.h"
using namespace std;

class LayerMapWalk;

class MapWalkConfigManager{
public:
	static void load(const string& ConfigFileName,LayerMapWalk* p_LayerMapWalk);
	static void save(const string& ConfigFileName,LayerMapWalk* p_LayerMapWalk);
};

#endif
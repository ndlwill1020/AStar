#ifndef _ROLE_H_
#define _ROLE_H_
#include "cocos2d.h"
USING_NS_CC;
#include <unordered_map>
using namespace std;

class Role : public Node{
public:
	Role();
	~Role();
	bool init();
	CREATE_FUNC(Role);

	enum State
	{
		None,
		// 向左走
		WalkLeft , 
		// 向右走
		WalkRight , 
		// 向上走
		WalkTop , 
		// 向下走
		WalkBottom
	};

	void setState(State type);
	void createActions();
	unordered_map< string , void* > UserData ; 
private:
	State m_state;
	

	Sprite * m_pSprMain ; 
	
	Vector<  Action* > m_Actions ;

	Size m_size ; 

	Action * m_pActWalkRight ; 
	Action * m_pActWalkLeft ;
	Action * m_pActWalkTop ;
	Action * m_pActWalkBottom ;
};

#endif
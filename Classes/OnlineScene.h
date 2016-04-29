#ifndef __ONLINE_SCENE___
#define __ONLINE_SCENE___
#include "cocos2d.h"
USING_NS_CC;
class OnlineScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(OnlineScene);
	bool init();
private:

};
#endif
#ifndef __NEXT_LEVEL_SCENE__
#define __NEXT_LEVEL_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class NextLevelScene : public Layer
{
public:
	CREATE_FUNC(NextLevelScene);
	bool init();
	static Scene* createScene();
private:

};
#endif
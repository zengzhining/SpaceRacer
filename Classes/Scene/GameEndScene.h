#ifndef _GAME_END__SCENE__
#define _GAME_END__SCENE__
#include "cocos2d.h"
USING_NS_CC;
class GameEndScene : public Layer
{
public:
	CREATE_FUNC(GameEndScene);
	bool init();
	static Scene* createScene();
private:

};
#endif
#ifndef __GAME_RULE_SCENE__
#define __GAME_RULE_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class GameRuleScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameRuleScene);
	bool init();
private:
	Menu* _menu;
};
#endif
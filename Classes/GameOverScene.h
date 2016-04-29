#ifndef __GAME_OVER_SCENE__
#define __GAME_OVER_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class GameOverScene : public Scene
{
public:
	static GameOverScene* create();
	bool initWithTexture();
private:

};
#endif
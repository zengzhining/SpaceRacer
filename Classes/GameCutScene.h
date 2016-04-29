#ifndef __GAMECUT_SCENE__
#define __GAMECUT_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class GameCutScene : public Layer
{
public:
	static Scene* createScene(Texture2D* texture);
	static GameCutScene* create( Texture2D* texture );
	bool initWithTexture(Texture2D* tex);

private:
};
#endif
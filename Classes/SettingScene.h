#ifndef __SETTING_SCENE__
#define __SETTING_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class SettingScene : public Layer
{
public:
	CREATE_FUNC(SettingScene);
	bool init();
	static Scene* createScene();
private:
	Menu* _menu;
};
#endif
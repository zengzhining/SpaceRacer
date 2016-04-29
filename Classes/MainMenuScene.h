#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class MainMenuScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(MainMenuScene);
	bool init();

	void onEnter() override;
	void onExit()  override;
private:
	Menu* _menu;
};
#endif
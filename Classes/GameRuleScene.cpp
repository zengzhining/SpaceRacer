#include "GameRuleScene.h"
USING_NS_CC;
Scene* GameRuleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameRuleScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameRuleScene::init()
{
	if (!Layer::init())
		return false;

	auto size = Director::getInstance()->getVisibleSize();
	MenuItemLabel* returnItem = MenuItemLabel::create(Label::createWithTTF("Return", "fonts/Pixel.ttf", 50), [](Ref* ref)
	{
		Director::getInstance()->popScene();
	});

	Vector<MenuItem*> menuArray;
	menuArray.pushBack(returnItem);
	_menu = Menu::createWithArray(menuArray);
	_menu->alignItemsVertically();
	_menu->setPosition(size.width / 2, size.height / 10);
	addChild(_menu);

	return true;
}
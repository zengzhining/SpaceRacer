#include "SettingScene.h"
#include "BgLayer.h"
USING_NS_CC;
Scene* SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	auto bgLayer = BgLayer::create();
	scene->addChild(bgLayer, -1);
	return scene;
}

bool SettingScene::init()
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
	_menu->setPosition(size.width / 2, size.height / 3);
	addChild(_menu);
	return true;
}
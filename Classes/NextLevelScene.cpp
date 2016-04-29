#include "NextLevelScene.h"
#include "HelloWorldScene.h"
#include "Data/GameData.h"
#include "BgLayer.h"
#include "Scene/GameEndScene.h"
USING_NS_CC;
Scene* NextLevelScene::createScene()
{
	auto scene = Scene::create();
	auto layer = NextLevelScene::create();
	scene->addChild(layer);
	scene->addChild(BgLayer::create(), -1);
	return scene;
}

bool NextLevelScene::init()
{
	auto size = Director::getInstance()->getVisibleSize();

	MenuItemLabel* contineItem = MenuItemLabel::create(Label::createWithTTF("Next", "fonts/Pixel.ttf", 50), [](Ref* ref){
		GameData::getInstance()->setGameRunning(true);
		int maxLevel = GameData::getInstance()->getMaxLevel();
		if (maxLevel > GameData::getInstance()->getLevel())
			Director::getInstance()->replaceScene(HelloWorld::createScene());
		else
			Director::getInstance()->replaceScene(GameEndScene::createScene());
	});

	MenuItemLabel* endGameItem = MenuItemLabel::create(Label::createWithTTF("End Game", "fonts/Pixel.ttf", 50), [](Ref* ref)
	{
		Director::getInstance()->end();
	});

	Vector<MenuItem*> menuArray;
	menuArray.pushBack(contineItem);
	menuArray.pushBack(endGameItem);
	auto menu = Menu::createWithArray(menuArray);
	menu->alignItemsVertically();
	menu->setPosition(size.width / 2, size.height / 2);
	addChild(menu);
	return true;
}
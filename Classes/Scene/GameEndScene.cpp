#include "GameEndScene.h"
#include "Data/GameData.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* GameEndScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameEndScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameEndScene::init()
{
	if (!Layer::init())
		return false;

	auto size = Director::getInstance()->getVisibleSize();

	auto lb = Label::createWithTTF("Finally I come to the End", "fonts/Pixel.ttf", 70);
	lb->setPosition(size.width / 2, size.height / 4 * 3);
	addChild(lb);

	MenuItemLabel* contineItem = MenuItemLabel::create(Label::createWithTTF("Continue", "fonts/Pixel.ttf", 50), [](Ref* ref){
		Director::getInstance()->replaceScene(HelloWorld::createScene());
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

	GameData::getInstance()->resetArmyNum();
	GameData::getInstance()->resetGameSpeed();
	GameData::getInstance()->resetLevel();
	return true;
}
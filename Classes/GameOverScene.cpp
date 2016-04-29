#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "Data/GameData.h"
#include "BgLayer.h"
USING_NS_CC;
GameOverScene* GameOverScene::create()
{
	auto scene = new GameOverScene();
	if (scene && scene->initWithTexture())
	{
		scene->autorelease();
		auto layer = BgLayer::create();
		scene->addChild(layer, -1);
		return scene;
	}
	return nullptr;
}

bool GameOverScene::initWithTexture()
{
	if (!Scene::init())
		return false;
	auto size = Director::getInstance()->getVisibleSize();

	MenuItemLabel* contineItem = MenuItemLabel::create(Label::createWithTTF("Resart", "fonts/Pixel.ttf", 50), [](Ref* ref){
		GameData::getInstance()->resetGameData();
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
	return true;
}
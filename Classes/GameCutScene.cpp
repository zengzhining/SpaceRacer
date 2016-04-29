#include "GameCutScene.h"
#include "HelloWorldScene.h"
#include "Data/GameData.h"
USING_NS_CC;
Scene* GameCutScene::createScene(Texture2D* texture)
{
	auto scene = Scene::create();
	auto layer = GameCutScene::create(texture);
	scene->addChild(layer);
	return scene;
}

GameCutScene* GameCutScene::create(Texture2D* texture)
{
	auto layer = new GameCutScene();
	if (layer->initWithTexture(texture) )
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

bool GameCutScene::initWithTexture(Texture2D* tex)
{
	if (!Layer::init())
		return false;
	auto size = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::createWithTexture(tex);
	bg->setFlippedY(true);
	bg->setPosition(size.width / 2, size.height / 2);
	addChild(bg);

	MenuItemLabel* contineItem = MenuItemLabel::create(Label::createWithTTF("Continue", "fonts/Pixel.ttf", 50), [](Ref* ref){
		GameData::getInstance()->setGameRunning(true);
		Director::getInstance()->popScene();
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
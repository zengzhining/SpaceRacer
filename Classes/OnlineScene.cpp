#include "OnlineScene.h"
USING_NS_CC;
Scene* OnlineScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OnlineScene::create();
	scene->addChild(layer);
	return scene;
}

bool OnlineScene::init()
{
	if (!Layer::init())
		return false;

	return true;
}
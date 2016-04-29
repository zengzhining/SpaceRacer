#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "BgLayer.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "OnlineScene.h"
#include "GameRuleScene.h"
USING_NS_CC;
Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	auto bg = BgLayer::create();
	scene->addChild(bg);
	scene->addChild(layer);
	return scene;
}
bool MainMenuScene::init()
{
	if (!Layer::init())
		return false;

	auto size = Director::getInstance()->getVisibleSize();
	auto title = Label::createWithTTF("Space Shooter", "fonts/Pixel.ttf", 60);
	title->setPosition(size.width / 2, size.height * 2 /3);
	addChild(title);

	auto hint = Label::createWithTTF("Touch Screen to Start", "fonts/Pixel.ttf", 30);
	hint->setPosition(size.width / 2, size.height / 4);
	addChild(hint);
	hint->runAction(RepeatForever::create(Sequence::create(FadeOut::create(2), FadeIn::create(2), NULL)));

	MenuItemLabel* single = MenuItemLabel::create(Label::createWithTTF("Single Mode", "fonts/Pixel.ttf", 50), [](Ref* ref){
		auto scene = TransitionProgressInOut::create(0.8, HelloWorld::createScene());
		Director::getInstance()->replaceScene(scene);
	});

	MenuItemLabel* onLine = MenuItemLabel::create(Label::createWithTTF("Online Mode", "fonts/Pixel.ttf", 50), [](Ref* ref)
	{
		Director::getInstance()->replaceScene(OnlineScene::createScene());
	});

	MenuItemLabel* gameRule = MenuItemLabel::create(Label::createWithTTF("Game Rule", "fonts/Pixel.ttf", 50), [](Ref* ref)
	{
		Director::getInstance()->pushScene(GameRuleScene::createScene());
	});

	MenuItemLabel* setting = MenuItemLabel::create(Label::createWithTTF("Setting", "fonts/Pixel.ttf", 50), [](Ref* ref)
	{
		Director::getInstance()->pushScene(SettingScene::createScene());
	});
	

	Vector<MenuItem*> menuArray;
	menuArray.pushBack(single);
	menuArray.pushBack(onLine);
	menuArray.pushBack(gameRule);
	menuArray.pushBack(setting);

	_menu = Menu::createWithArray(menuArray);
	_menu->alignItemsVertically();
	_menu->setPosition(size.width / 2, size.height / 3);
	_menu->setVisible(false);
	addChild(_menu);
	for (auto itr = menuArray.begin(); itr != menuArray.end(); ++itr)
	{
		auto item = (*itr);
		item->setScale(0.3f);
	}
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this, hint, menuArray](Touch* touch, Event* event){
		//Director::getInstance()->replaceScene(HelloWorld::createScene());
		_menu->setVisible(true);
		hint->stopAllActions();
		hint->setVisible(false);
		for (int index = 0; index < menuArray.size(); ++index)
		{
			auto item = menuArray.at(index);
			auto act = ScaleTo::create((index+ 1) * 0.1f, 1.0f);
			item->runAction(act);
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void MainMenuScene::onEnter()
{
	Layer::onEnter();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/mainMenu.mp3", true);
}

void MainMenuScene::onExit()
{
	Layer::onExit();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
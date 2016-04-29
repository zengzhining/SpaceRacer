#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "BgLayer.h"
#include "Game.h"
#include "GameCutScene.h"
#include "GameOverScene.h"
#include "NextLevelScene.h"
#include <cmath>
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
	auto bg = BgLayer::create();
	scene->addChild(bg);
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	this->initData();
	this->addCamera();
	this->playBg();
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (this->addReource())
	{
		this->addUI();
		this->addMainPlane();
		this->addRenderTexture();
		this->addTitle();
		//开启定时器
		scheduleUpdate();
		auto act = Sequence::create(DelayTime::create(3.0f), CallFunc::create([this](){
			this->createArmy();
			this->addEvent();
		}), NULL);
		this->runAction(act);

	}

	return true;
}

void HelloWorld::playBg()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/mainBg.mp3", true);
}

void HelloWorld::initData()
{
	GameData::getInstance()->loadLevelInfo(GameData::getInstance()->getLevel());
	srand(time(NULL));
	isTouchFromOutSide_ = true;

}

void HelloWorld::addCamera()
{
	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	addChild(camera);
}

void HelloWorld::addRenderTexture()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	rex_ = RenderTexture::create(visibleSize.width, visibleSize.height);
	rex_->retain();
}

void HelloWorld::addMainPlane()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_mainPlane = Space::HeroPlane::create( Space::Plane::HERO );
	_mainPlane->retain();
	_mainPlane->setPosition(visibleSize.width / 2, -_mainPlane->getContentSize().height / 2);
	addChild(_mainPlane, OBJOrder::ROLE);
	auto act = EaseSineIn::create(MoveTo::create(3.0f, Vec2(visibleSize.width / 2, _mainPlane->getContentSize().height / 2 + leftBtn_->getContentSize().height * 2)));
	_mainPlane->runAction(act);
	GameData::getInstance()->setMainPlane(_mainPlane);
}

void HelloWorld::addUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//添加血条
	hpBar_ = HpBar::create("HpBarEmpty.png", "HpBarFull.png");
	auto hpBarSize = hpBar_->getContentSize();
	hpBar_->setPosition(visibleSize.width - hpBarSize.width / 2, visibleSize.height + hpBarSize.height / 2);
	addChild(hpBar_, OBJOrder::UI);
	hpBar_->setCameraMask(2);
	auto actHp = Sequence::create(DelayTime::create(3.0f), EaseSineIn::create(MoveTo::create(0.6f, Vec2(visibleSize.width - hpBarSize.width / 2, visibleSize.height - hpBarSize.height / 2))), NULL);
	hpBar_->runAction(actHp);

	//添加分数
	scoreChar = new char[20];
	sprintf(scoreChar, "Score:%d", GameData::getInstance()->getGameScore());
	gameScore_ = Label::createWithTTF(scoreChar, "fonts/Pixel.ttf", 30);
	gameScore_->setAnchorPoint(Vec2(0, 0.5f));
	gameScore_->setPosition(0, visibleSize.height + gameScore_->getContentSize().height / 2);
	addChild(gameScore_, OBJOrder::UI);
	gameScore_->setCameraMask(2);
	auto actScore = Sequence::create(DelayTime::create(3.0f), EaseBackIn::create(MoveTo::create(0.6f, Vec2(0, visibleSize.height - gameScore_->getContentSize().height / 2))), NULL);
	gameScore_->runAction(actScore);

	//添加按钮
	leftBtn_ = Sprite::createWithSpriteFrameName("playbtndarkcyan0001.png");
	leftBtn_->setFlippedX(true);
	leftBtn_->setScale(2, 2);
	addChild(leftBtn_, OBJOrder::UI);
	leftBtn_->setContentSize(Size(leftBtn_->getContentSize().width * 2, leftBtn_->getContentSize().height * 2));
	leftBtn_->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0001.png"));
	leftBtn_->setPosition(leftBtn_->getContentSize().width, -leftBtn_->getContentSize().height);
	leftBtn_->setCameraMask(2);
	auto actLeft = Sequence::create( DelayTime::create(3.0f),EaseExponentialIn::create(MoveTo::create(0.4f, Vec2(leftBtn_->getContentSize().width, leftBtn_->getContentSize().height))), NULL);
	leftBtn_->runAction(actLeft);

	rightBtn_ = Sprite::createWithSpriteFrameName("playbtndarkcyan0001.png");
	rightBtn_->setScale(2, 2);
	addChild(rightBtn_, OBJOrder::UI);
	rightBtn_->setContentSize(Size(rightBtn_->getContentSize().width * 2, rightBtn_->getContentSize().height * 2));
	rightBtn_->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0001.png"));
	rightBtn_->setPosition(rightBtn_->getContentSize().width * 2.0 + leftBtn_->getPositionX(), -rightBtn_->getContentSize().height);
	rightBtn_->setCameraMask(2);
	auto actRight = Sequence::create(DelayTime::create(3.0f), EaseExponentialIn::create(MoveTo::create(0.6f, Vec2(rightBtn_->getContentSize().width * 2.0 + leftBtn_->getPositionX(), rightBtn_->getContentSize().height))), NULL);
	rightBtn_->runAction(actRight);

	fireBtn_ = Sprite::createWithSpriteFrameName("buttonsquaredarkcyan0001.png");
	fireBtn_->setScale(4, 4);
	addChild(fireBtn_, OBJOrder::UI);
	fireBtn_->setContentSize(Size(fireBtn_->getContentSize().width * 2, fireBtn_->getContentSize().height * 2));
	fireBtn_->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("buttonsquaredarkcyan0001.png"));
	fireBtn_->setPosition(visibleSize.width - fireBtn_->getContentSize().width * 2, -fireBtn_->getContentSize().height * 2);
	fireBtn_->setCameraMask(2);
	auto actFire = Sequence::create(DelayTime::create(3.0f), EaseExponentialIn::create(MoveTo::create(0.8f, Vec2(visibleSize.width - fireBtn_->getContentSize().width * 2, fireBtn_->getContentSize().height * 2))), NULL);
	fireBtn_->runAction(actFire);

	GameData::getInstance()->setLeftBtn(leftBtn_);
	GameData::getInstance()->setRightBtn(rightBtn_);
	GameData::getInstance()->setFireBtn(fireBtn_);
}
void HelloWorld::addTitle()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto title = Label::createWithTTF("", "fonts/Pixel.ttf", 70);
	title->setPosition(visibleSize.width / 2, visibleSize.height / 4 * 3);
	title->setString(GameData::getInstance()->getTaskTitle());
	title->setOpacity(0);
	addChild(title, OBJOrder::UI);
	auto act = Sequence::create(DelayTime::create(1.0f),FadeIn::create(0.3f), DelayTime::create(0.3f), FadeOut::create(1.0f), RemoveSelf::create(true), NULL);
	title->runAction(act);
}

void HelloWorld::createArmy()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto armyInfo = GameData::getInstance()->getArmyInfo();
	for (int i = 1; i <= armyInfo->getArmyNumInLevel(); i++)
	{
		int num = random(1, 3);
		auto army = Space::Plane::create( (Space::Plane::PlaneType)num );
		army->setPosition(this->getArmyPosX(armyInfo->getPosX(i), army->getContentSize().width), visibleSize.height + army->getContentSize().height / 2 + _mainPlane->getContentSize().height * i * 3);
		army->setSpeedY(armyInfo->getSpeedY(i));
		addChild(army, OBJOrder::ROLE);
		planes_.pushBack(army);
	}
}

float HelloWorld::getArmyPosX(float index, const float armyWidth)
{
	auto size = Director::getInstance()->getVisibleSize();
	float limitX = size.width - armyWidth / 2;
	float startX = armyWidth / 2;
	float posX = index * armyWidth;
	if (posX < startX)
		posX = startX;
	if (posX > limitX)
		posX = limitX;
	return posX;
}

void HelloWorld::addEvent()
{
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	const char* MAIN_PLANE_DIE = "mainPlaneDie";
	eventDispatcher->addCustomEventListener(MAIN_PLANE_DIE, [this](EventCustom* event){
		this->goGameOverScene();
	});

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [this](const std::vector<Touch*>& touches, Event* event){
		auto size = Director::getInstance()->getVisibleSize();
		auto touch = touches.front();
		auto location = touch->getLocation();
		if (location.y > size.height / 2)
		{
			GameData::getInstance()->setGameRunning(false);
			this->gameCut();
			return;
		}
		//在左边矩形区域内是改变方向区域,如果是从外面到内部就取消
		if (location.x <= size.width / 2 && location.y <= size.height / 3)

		{
			touchDir_ = touch;
		}
		if (location.x >= size.width / 2 && location.y <= size.height / 3)
		{
			touchFire_ = touch;
		}
		if (touchDir_ == touch)
			_mainPlane->handleTouchDirectionMoved(touchDir_, event);
		if (touchFire_ == touch)
			_mainPlane->handleTouchFireMoved(touchFire_, event);
	};
	listener->onTouchesMoved = [this](const std::vector<Touch*>& touches, Event* event)
	{
		auto size = Director::getInstance()->getVisibleSize();
		if (touches.size() >= 3)
			return;
		for (auto itr = touches.begin(); itr != touches.end(); ++itr)
		{
			auto touch = (*itr);
			auto location = touch->getLocation();
			auto preLocation = touch->getPreviousLocation();
			//在左边矩形区域内是改变方向区域,如果是从外面到内部就取消
			if (location.x <= size.width / 2 && location.y <= size.height / 3)

			{
				touchDir_ = touch;
			}
			if (location.x >= size.width / 2 && location.y <= size.height / 3)
			{
				touchFire_ = touch;
			}
			if (touchDir_ == touch)
				_mainPlane->handleTouchDirectionMoved(touchDir_, event);
			if (touchFire_ == touch)
				_mainPlane->handleTouchFireMoved(touchFire_, event);
		}
	};
	listener->onTouchesEnded = [this](const std::vector<Touch*>& touches, Event* event)
	{
		for (auto itr = touches.begin(); itr != touches.end(); ++itr)
		{
			auto touch = *itr;
			auto location = touch->getLocation();
			if (touch == touchDir_)
			{
				touchDir_ = nullptr;
				_mainPlane->handleTouchDirectEnded(touch, event);
			}

			if (touch == touchFire_)
			{
				touchFire_ = nullptr;
				_mainPlane->handleTouchFireEnded(touch, event);
			}

		}
	};
	listener->onTouchesCancelled = [this](const std::vector<Touch*>& touches, Event* event)
	{
	};

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event* event){
		if (code == EventKeyboard::KeyCode::KEY_BACK)
		{
			GameData::getInstance()->setGameRunning(false);
			this->gameCut();
		}
	};

	keyListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event* event){
	
	};
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::goMenuScene()
{
	auto scene = MainMenuScene::createScene();
	GameData::getInstance()->resetGameData();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::goGameOverScene()
{
	auto scene = GameOverScene::create();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::restart()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

bool HelloWorld::addReource()
{
	auto texManager = Director::getInstance()->getTextureCache();

	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);

	Texture2D* pTexture = texManager->addImage("Plane/Plane.png");

	if (pTexture)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plane/Plane.plist", pTexture);
		return true;
	}
	return false;
}

void HelloWorld::update(float delta)
{
	if (!GameData::getInstance()->isGameRunning())
	{
		return;
	}
	updateCollsion(delta);
	updateUI();
	updateLogic();
}

void HelloWorld::updateLogic()
{
	auto itr = planes_.begin();
	for (itr; itr != planes_.end(); ++itr)
	{
		auto plane = *itr;
		//超出场景剔除游戏
		if (plane->getPositionY() < -(plane->getContentSize().height / 2))
		{
			plane->removeFromParent();
			itr = planes_.erase(itr);
			GameData::getInstance()->addGameScore(200);
			GameData::getInstance()->addArmyNum(1);
			//判断游戏是否结束
			if (Task::TYPE::ARMY_NUM == GameData::getInstance()->getTaskType() && GameData::getInstance()->getArmyNum() >= GameData::getInstance()->getLimitArmyNum())
			{
				auto size = Director::getInstance()->getVisibleSize();
				auto act = Sequence::create(DelayTime::create(3), CallFunc::create([this](){
					this->nextLevel();	
				}), NULL);
				this->runAction(act);
				auto title = Label::createWithTTF("Mission Complete", "fonts/Pixel.ttf", 70);
				title->setPosition(size.width / 2, size.height / 3 * 2);
				this->addChild(title, OBJOrder::UI);
				auto actTitle = Sequence::create(ScaleTo::create(2.0f, 1.5f), FadeIn::create(1.0f), NULL);
				title->runAction(actTitle);
			}

			if (itr == planes_.end())
				break;
		}
	}
}

void HelloWorld::nextLevel()
{
	GameData::getInstance()->addLevel(1);
	GameData::getInstance()->updateTask();
	GameData::getInstance()->resetArmyNum();
	Director::getInstance()->replaceScene(NextLevelScene::createScene());
}

void HelloWorld::updateUI()
{
	sprintf(scoreChar, "Score:%d", GameData::getInstance()->getGameScore());
	gameScore_->setString(scoreChar);
}

void HelloWorld::updateCollsion(float dt)
{
	auto size = Director::getInstance()->getVisibleSize();
	bool isEmpty = planes_.empty();
	if (isEmpty)
		return;
	auto itr = planes_.begin();
	for (itr; itr != planes_.end(); ++itr)
	{
		auto plane = *itr;
		//碰撞检测
		if (_mainPlane && _mainPlane->getParent() == NULL)
		{
			_mainPlane->release();
			_mainPlane = NULL;
		}

		if (_mainPlane )
		{
			auto mainPlaneBox = _mainPlane->getBoundingBox();
			Rect mainSize = Rect(mainPlaneBox.origin.x, mainPlaneBox.origin.y, mainPlaneBox.size.width * 3/5, mainPlaneBox.size.height * 3 /5);
			if (mainSize.intersectsRect(plane->getBoundingBox()))
			{
				//敌机撞到了
				bool isHurt = _mainPlane->isHurt();
				if (!isHurt)
				{
					_mainPlane->onHurt(1);
					hpBar_->minitesHp(1 / 3.0f * 100);
					if (_mainPlane->getHp() <= 0)
					{
						_mainPlane->explode();
					}

				}
			}
		}

	}
}

void HelloWorld::gameCut()
{
	rex_->beginWithClear(0, 0, 0, 1);
	Director::getInstance()->getRunningScene()->visit();
	rex_->end();

	Director::getInstance()->pushScene(GameCutScene::createScene(rex_->getSprite()->getTexture()));
}

void HelloWorld::onEnter()
{
	Node::onEnter();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void HelloWorld::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
}

void HelloWorld::onExit()
{
	Node::onExit();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}
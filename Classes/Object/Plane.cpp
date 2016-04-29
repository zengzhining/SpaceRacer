#include "Plane.h"
#include "Data/GameData.h"
#include "Data/EventConst.h"
#include "SimpleAudioEngine.h"
using namespace Space;
Plane* Plane::create(Plane::PlaneType typeId)
{
	auto plane = new Plane();
	if (plane && plane->init(typeId))
	{
		plane->autorelease();
		return plane;
	}
		 
	return nullptr;
}

bool Plane::init(Plane::PlaneType typeId)
{
	std::string frameName;
	switch (typeId)
	{
	case Space::Plane::GREEN:
		frameName = "GreenPlane.png";
		break;
	case Space::Plane::GREY:
		frameName = "GreyPlane.png";
		break;
	case Space::Plane::RED:
		frameName = "RedPlane.png";
		break;
	case Space::Plane::HERO:
		frameName = "FriendPlane01.png";
		break;
	default:
		break;
	}

	if (cocos2d::Sprite::initWithSpriteFrameName(frameName))
	{
		speed_ = cocos2d::Vec2::ZERO;
		isExplode_ = false;
		maxHp_ =  hp_  = 3 ;
		isHurt_ = false;
		fxId_ = 0;
		hasPlay_ = false;
		this->setRotation(180);
		return true;

	}
	return false;
}

void Plane::onEnter()
{
	Sprite::onEnter();
	scheduleUpdate();
}

void Plane::onExit()
{
	Sprite::onExit();
}

void Plane::update(float delta)
{
	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	updatePosition();
	if (this->getPositionY() < size.height && this->getPositionY() > 0 && hasPlay_ == false)
	{
		/*this->playMovedFX("FX/EnemyIn.wav");*/
		hasPlay_ = true;
	}
	updateLogic();
}

void Plane::updateLogic()
{

}

void Plane::updatePosition()
{
	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	auto pos = this->getPosition();
	auto finalPos = pos + speed_ * GameData::getInstance()->getGameSpeed();
	if (finalPos.x > (size.width - this->getContentSize().width/2))
	{
		finalPos = pos;
	}

	if (finalPos.x < (this->getContentSize().width / 2))
	{
		finalPos = pos;
	}
	this->setPosition(finalPos);
}
void Plane::setSpeed(const cocos2d::Vec2 speed)
{
	speed_ = speed;
}

void Plane::setSpeed(const float speedX, const float speedY)
{
	this->setSpeed(cocos2d::Vec2(speedX, speedY));
}

void Plane::setSpeedX(const float speedX)
{
	this->setSpeed(speedX, speed_.y);
}

void Plane::setSpeedY(const float speedY)
{
	this->setSpeed(speed_.x, speedY);
}

cocos2d::Vec2 Plane::getSpeed() const
{
	return speed_;
}

void Plane::onHurt(const float deltaHp)
{
	this->minitesHp(deltaHp);
	this->setHurt(true);
	this->scheduleOnce(schedule_selector(Plane::hurt), 1.0);
}

void Plane::hurt(float dt)
{
	this->setHurt(false);
}

void Plane::setHurt(bool isHurt)
{
	USING_NS_CC;
	isHurt_ = isHurt;
	if (isHurt == true)
	{
		auto act = Repeat::create(Sequence::create(FadeOut::create(0.1f), FadeIn::create(0.2f), NULL), 3);
		this->runAction(act);
	}
	else
		this->setOpacity(255);
	
}

bool Plane::isHurt() const
{
	return isHurt_;
}

void Plane::explode()
{
	if (this->isExplode() == true)
		return;

	using namespace cocos2d;
	Animation* ani = AnimationCache::getInstance()->getAnimation("planeExplode");
	if (ani == NULL)
	{
		Vector<SpriteFrame*> frames;
		char explodeName[20];
		for (int i = 1; i < 5; i++)
		{
			sprintf(explodeName, "PlaneExplose%02d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(explodeName);
			frames.pushBack(frame);
		}
		ani = Animation::createWithSpriteFrames(frames, 0.1f);
		AnimationCache::getInstance()->addAnimation(ani, "planeExplode");
	}
	auto act = Sequence::create(Animate::create(ani), RemoveSelf::create(true), CallFunc::create([](){
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MAIN_PLANE_DIE);
	}), NULL);
	this->runAction( act );
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX/Explosion.wav");
	isExplode_ = true;
}

bool Plane::isExplode()
{
	return isExplode_;
}

void Plane::playMovedFX(std::string fileName)
{
	fxId_ = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fileName.c_str(), false);
}

void Plane::stopMovedFx()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(fxId_);
	fxId_ = 0;
}
//HeroPlane

HeroPlane* HeroPlane::create(const Plane::PlaneType typeId)
{
	HeroPlane* plane = new HeroPlane();
	if (plane && plane->init(typeId))
	{
		plane->autorelease();
		return plane;
	}
		
	return nullptr;
}

bool HeroPlane::init(const Plane::PlaneType typeId)
{
	if (Plane::init(typeId))
	{
		this->setRotation(0);
		this->handleInput();
		return true;
	}

	return false;
	
}

void HeroPlane::handleInput()
{
	using namespace cocos2d;
	auto boardListener = EventListenerKeyboard::create();
	boardListener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event* event){
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->setSpeedX(-10);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->setSpeedX(10);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			GameData::getInstance()->setGameSpeed(GameData::getInstance()->getDefaultGameSpeed() * 2);
			break;
		default:
			break;
		}
	};
	boardListener->onKeyReleased = [this](EventKeyboard::KeyCode code, Event* event){
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->setSpeedX(0);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->setSpeedX(0);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			GameData::getInstance()->resetGameSpeed();
			break;
		default:
			break;
		}
	};
	
	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(boardListener, this);


}

bool HeroPlane::handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	using namespace cocos2d;
	auto size = Director::getInstance()->getVisibleSize();
	auto location = touch->getLocation();
	auto leftBtn = GameData::getInstance()->getLeftBtn();
	auto rightBtn = GameData::getInstance()->getRightBtn();
	auto fireBtn = GameData::getInstance()->getFireBtn();
	if (leftBtn->getBoundingBox().containsPoint(location))
	{
		this->setSpeedX(-10);
		leftBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0002.png"));

	}
	if (rightBtn->getBoundingBox().containsPoint(location))
	{
		this->setSpeedX(10);
		rightBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0002.png"));
	}
	if (fireBtn->getBoundingBox().containsPoint(location))
	{
		GameData::getInstance()->setGameSpeed(GameData::getInstance()->getDefaultGameSpeed() * 2);
		fireBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("buttonsquaredarkcyan0002.png"));
	}
	return true;
}

void HeroPlane::handleTouchDirectionMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	using namespace cocos2d;
	auto size = Director::getInstance()->getVisibleSize();
	auto location = touch->getLocation();
	auto leftBtn = GameData::getInstance()->getLeftBtn();
	auto rightBtn = GameData::getInstance()->getRightBtn();
	auto fireBtn = GameData::getInstance()->getFireBtn();
	if (leftBtn->getBoundingBox().containsPoint(location))
	{
		this->setSpeedX(-10);
		leftBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0002.png"));
	}
	else
	{
		leftBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0003.png"));
	}
	if (rightBtn->getBoundingBox().containsPoint(location))
	{
		this->setSpeedX(10);
		rightBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0002.png"));
	}
	else
	{
		rightBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0003.png"));
	}
}

void HeroPlane::handleTouchFireMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	using namespace cocos2d;
	auto size = Director::getInstance()->getVisibleSize();
	auto location = touch->getLocation();
	auto leftBtn = GameData::getInstance()->getLeftBtn();
	auto rightBtn = GameData::getInstance()->getRightBtn();
	auto fireBtn = GameData::getInstance()->getFireBtn();
	if (fireBtn->getBoundingBox().containsPoint(location))
	{
		auto speed = GameData::getInstance()->getDefaultGameSpeed();
		GameData::getInstance()->setGameSpeed(speed * 2);
		fireBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("buttonsquaredarkcyan0002.png"));
	}
	else
	{
		fireBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("buttonsquaredarkcyan0003.png"));
	}
}
void HeroPlane::handleTouchFireEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	using namespace cocos2d;
	auto size = Director::getInstance()->getVisibleSize();
	auto location = touch->getLocation();
	auto fireBtn = GameData::getInstance()->getFireBtn();
	if (fireBtn->getBoundingBox().containsPoint(location))
	{
		fireBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("buttonsquaredarkcyan0003.png"));
		GameData::getInstance()->resetGameSpeed();
	}
}

void HeroPlane::handleTouchDirectEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	using namespace cocos2d;
	auto size = Director::getInstance()->getVisibleSize();
	auto location = touch->getLocation();
	auto leftBtn = GameData::getInstance()->getLeftBtn();
	auto rightBtn = GameData::getInstance()->getRightBtn();
	if (leftBtn->getBoundingBox().containsPoint(location))
	{
		leftBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0003.png"));
		this->setSpeedX(0);
	}
	if (rightBtn->getBoundingBox().containsPoint(location))
	{
		rightBtn->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playbtndarkcyan0003.png"));
		this->setSpeedX(0);
	}
}

void HeroPlane::setSpeed(const cocos2d::Vec2 speed)
{
	speed_ = speed;
	if (speed.x > 0 || speed.x < 0 || speed.y > 0 || speed.y < 0)
		this->playMovedFX("FX/MainFly.wav");
	else
		this->stopMovedFx();
}

void HeroPlane::playMovedFX(std::string fileName)
{
	if (fxId_ == 0)
	{
		fxId_ = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fileName.c_str(), true);
	}
}

void HeroPlane::onHurt(const float deltaHp)
{
	Plane::onHurt(deltaHp);
	using namespace cocos2d;
	auto size = Director::getInstance()->getVisibleSize();
	auto camera = Camera::getDefaultCamera();
	auto moveAct = MoveBy::create(0.2f, Vec2(0, size.height/100));
	auto act = EaseSineInOut::create(Sequence::create(moveAct, moveAct->reverse(), NULL));
	camera->runAction(act);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX/Hurt.wav");
}
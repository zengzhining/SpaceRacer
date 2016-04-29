#include "Bullet.h"
#include "Data/GameData.h"
USING_NS_CC;
Bullet* Bullet::create( const std::string frameName , const std::string secName, const std::string thirdName )
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->init(frameName, secName, thirdName))
	{
		bullet->autorelease();
		return bullet;
	}
		
	return bullet;
}

bool Bullet::init(const std::string frameName, const std::string secName, const std::string thirdName)
{
	if (Sprite::initWithSpriteFrameName(frameName))
	{
		firstRes_ = frameName;
		secondRes_ = secName;
		thirdRes_ = thirdName;
		this->setSpeed(Vec2::ZERO);
		scheduleUpdate();
		return true;
	}
	return false;
}

void Bullet::onEnter()
{
	Sprite::onEnter();
	auto act = Sequence::create(DelayTime::create(0.1), CallFunc::create([this](){
		this->setSpriteFrame(secondRes_);
	}), DelayTime::create(0.1), CallFunc::create([this](){
		this->setSpriteFrame(thirdRes_);
	}), NULL);
	this->runAction(act);
}

void Bullet::update(float delta)
{
	updatePosition();
}

void Bullet::setSpeed(Vec2 speed)
{
	speed_ = speed;
}

Vec2& Bullet::getSpeed()
{
	return speed_;
}

void Bullet::updatePosition()
{
	Vec2 pos = this->getPosition();
	Vec2 finalPos = pos + speed_ * GameData::getInstance()->getGameSpeed();
	this->setPosition(finalPos);
}

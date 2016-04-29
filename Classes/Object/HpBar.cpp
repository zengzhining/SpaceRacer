#include "HpBar.h"
USING_NS_CC;
HpBar* HpBar::create(std::string backFile, std::string barFile)
{
	HpBar* bar = new HpBar();
	if (bar)
	{
		if (bar->init(backFile, barFile))
		{
			bar->autorelease();
			return bar;
		}
			
	}
	return nullptr;
}

bool HpBar::init(std::string backFile, std::string barFile)
{
	backGround_ = Sprite::createWithSpriteFrameName(backFile);
	this->addChild(backGround_);

	barRes_ = Sprite::createWithSpriteFrameName(barFile);
	hpBar_ = ProgressTimer::create(barRes_);
	hpBar_->setType(ProgressTimer::Type::BAR);
	hpBar_->setBarChangeRate(Vec2(1, 0));
	hpBar_->setMidpoint(Vec2(1, 0.5));
	hpBar_->setPercentage(100);

	this->addChild(hpBar_);

	this->setScale(0.4f);
	auto act = ScaleTo::create(0.1f, 1.0f);
	this->runAction(act);

	return true;
}

void HpBar::setPercentage(float percent)
{
	hpBar_->setPercentage(percent);
}

float HpBar::getPercentage() const
{
	return hpBar_->getPercentage();
}

void HpBar::minitesHp(const float deltaPercent)
{
	this->runAction(HpProgressTo::create(0.5, this->getPercentage() - deltaPercent));
}

void HpBar::onEnter()
{
	Node::onEnter();
}

const Size& HpBar::getContentSize() const
{
	return backGround_->getContentSize();
}

//HPProgressTo Action
HpProgressTo* HpProgressTo::create(float duration, float percent)
{
	HpProgressTo *progressTo = new (std::nothrow) HpProgressTo();
	progressTo->initWithDuration(duration, percent);
	progressTo->autorelease();

	return progressTo;
}

HpProgressTo* HpProgressTo::clone() const
{
	// no copy constructor    
	auto a = new (std::nothrow) HpProgressTo();
	a->initWithDuration(_duration, _to);
	a->autorelease();

	return a;
}

void HpProgressTo::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	_from = ((HpBar*)(target))->getPercentage();
}

void HpProgressTo::update(float time)
{
	((HpBar*)(_target))->setPercentage(_from + (_to - _from) * time);
}
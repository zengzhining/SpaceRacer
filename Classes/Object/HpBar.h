#ifndef __HPBAR___
#define __HPBAR___
#include "cocos2d.h"
USING_NS_CC;
class HpBar : public Node
{
public:
	static HpBar* create(std::string backFile, std::string barFile);

	bool init( std::string backFile, std::string barFile );

	virtual void onEnter() override;

	void setPercentage(float percent);

	float getPercentage() const ;

	void minitesHp(const float deltaPercent);

	virtual const Size& getContentSize() const override;

private:
	Sprite* backGround_;
	Sprite* barRes_;
	ProgressTimer* hpBar_;
};

class HpProgressTo : public ProgressTo
{
public:
	static HpProgressTo* create(float duration, float percent);

	virtual HpProgressTo* clone() const override;
	virtual void startWithTarget(Node *target) override;
	virtual void update(float time) override;

};
#endif
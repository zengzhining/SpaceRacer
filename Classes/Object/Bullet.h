#ifndef __Bullet___
#define __Bullet___
#include "cocos2d.h"
USING_NS_CC;
class Bullet : public Sprite
{
public:
	static Bullet* create( const std::string frameName , const std::string secName, const std::string thirdName );
	bool init(const std::string frameName, const std::string secName, const std::string thirdName);

	void update(float delta) override;

	void setSpeed(Vec2 speed);

	Vec2& getSpeed();

	void onEnter() override;

private:
	Vec2 speed_;
	std::string firstRes_;
	std::string secondRes_;
	std::string thirdRes_;

	void updatePosition();
};

#endif
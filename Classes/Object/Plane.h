#ifndef __PLANE___
#define __PLANE___
#include "cocos2d.h"
#include "InterFace/Controller.h"
namespace Space
{
	class Plane : public cocos2d::Sprite
	{
	public:
		enum PlaneType
		{
			HERO = 0,
			GREEN,
			GREY,
			RED,
		};
		static Plane* create(const Plane::PlaneType typeId);

		virtual bool init(const Plane::PlaneType typeId);

		void update(float delta) override;
		void updatePosition();
		void updateLogic();

		void onEnter() override;
		void onExit() override;

		virtual void setSpeed(const cocos2d::Vec2 speed);
		void setSpeed(const float speedX, const float speedY);
		void setSpeedX(const float speedX);
		void setSpeedY(const float speedY);

		void hurt( float dt);
		virtual void onHurt(const float deltaHp);

		//设置血量
		void setHp(const float hpValue){ hp_ = hpValue; }
		float getHp() const { return hp_; };
		void minitesHp(const float hpValue){ hp_ -= hpValue; }

		void setMaxHp(const float maxHp){ maxHp_ = maxHp; }
		float getMaxHp() const { return maxHp_; }

		//是否爆炸
		bool isExplode();
		void explode();

		//是否受伤
		void setHurt(bool isHurt);
		bool isHurt() const;

		cocos2d::Vec2 getSpeed() const;

		//播放音效
		virtual void playMovedFX( std::string fileName );
		virtual void stopMovedFx();

	protected:
		cocos2d::Vec2 speed_;
		bool isExplode_;
		float hp_;
		float maxHp_;
		bool isHurt_;
		unsigned int fxId_;
		bool hasPlay_;
		PlaneType type_;

	};

	class HeroPlane : public Plane, public Space::Controller
	{
	public:
		static HeroPlane* create(const Plane::PlaneType typeId);

		bool init(const Plane::PlaneType typeId) override;

		virtual void onHurt(const float deltaHp) override;
		virtual void playMovedFX(std::string fileName) override;

		virtual void setSpeed(const cocos2d::Vec2 speed);

		virtual void handleInput();

		virtual bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void handleTouchDirectionMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void handleTouchFireMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void handleTouchDirectEnded(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void handleTouchFireEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	};
};
#endif
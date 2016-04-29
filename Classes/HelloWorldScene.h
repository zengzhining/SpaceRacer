#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
#include "Object/Plane.h"
#include "Object/HpBar.h"

class HelloWorld : public cocos2d::Layer
{
public:
	enum OBJOrder
	{
		BACKGROUND,
		ROLE,
		UI,
	};
    static cocos2d::Scene* createScene();

    virtual bool init();
	void initData();

	void addCamera();
	bool addReource();
	void addEvent();
	void addTitle();
	void addUI();
	void addMainPlane();
	void addRenderTexture();
	void createArmy();

	void playBg();
    
	void updateUI();
	void updateCollsion(float dt);
	void updateLogic();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	float getArmyPosX(float index, const float armyWidth);

	void goMenuScene();
	void goGameOverScene();
	void gameCut();
	void restart();
	void nextLevel();

	void update(float delta) override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
public:
	Space::HeroPlane* _mainPlane;
	HpBar* hpBar_;
	Label* gameScore_;
	cocos2d::Vector<Space::Plane*> planes_;
	Sprite* leftBtn_;
	Sprite* rightBtn_;
	Sprite* fireBtn_;


	cocos2d::Touch* touchDir_;
	cocos2d::Touch* touchFire_;
	bool isTouchFromOutSide_;

	cocos2d::RenderTexture* rex_;
	char* scoreChar;
};

#endif // __HELLOWORLD_SCENE_H__

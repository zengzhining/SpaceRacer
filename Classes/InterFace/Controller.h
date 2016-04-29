#ifndef __CONTROLLER___
#define __CONTROLLER___
#include "cocos2d.h"
namespace Space
{
	class Controller
	{
	public:
		virtual void handleInput() = 0;
		virtual bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) = 0;
		virtual	void handleTouchDirectionMoved(cocos2d::Touch* touch, cocos2d::Event* event) = 0;
		virtual void handleTouchFireMoved(cocos2d::Touch* touch, cocos2d::Event* event) = 0;
		virtual void handleTouchFireEnded(cocos2d::Touch* touch, cocos2d::Event* event) = 0;
		virtual void handleTouchDirectEnded(cocos2d::Touch* touch, cocos2d::Event* event) = 0;

	};
}


#endif
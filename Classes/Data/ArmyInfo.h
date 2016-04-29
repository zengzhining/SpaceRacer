#ifndef __ARMY_INFO___
#define __ARMY_INFO___
#include "cocos2d.h"
class ArmyInfo
{
public:
	ArmyInfo(){};
	~ArmyInfo(){};

	bool init(cocos2d::ValueMap& map);
	static ArmyInfo* create(cocos2d::ValueMap& map);
	int getArmyNumInLevel() const { return num_; }
	float getPosX(int index);
	float getSpeedY(int index);
private:
	int num_;
	cocos2d::ValueMap info_;
};
#endif

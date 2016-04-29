#include "ArmyInfo.h"
USING_NS_CC;
ArmyInfo* ArmyInfo::create(ValueMap& map)
{
	auto info = new ArmyInfo();
	if (info && info->init(map))
		return info;
	return nullptr;
}

bool ArmyInfo::init(ValueMap& map)
{
	num_ = map.size();
	info_ = map;

	return true;
}

float ArmyInfo::getPosX(int index)
{
	char armyName[20];
	sprintf(armyName, "Army%03d", index);
	auto info = info_[armyName].asValueMap();
	return info["PosX"].asFloat();
}

float ArmyInfo::getSpeedY(int index)
{
	char armyName[20];
	sprintf(armyName, "Army%03d", index);
	auto info = info_[armyName].asValueMap();
	return info["SpeedY"].asFloat();
}
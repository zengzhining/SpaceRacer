#include "GameData.h"

//单例
static GameData* g_gamedata = nullptr;

GameData::GameData() 
	:gameSpeed_(1.0f)
	,originGameSpeed_(1.0f)

{
}

GameData::~GameData()
{

}

GameData* GameData::getInstance()
{
	if (g_gamedata == nullptr)
	{
		g_gamedata = new GameData();
		if (g_gamedata && g_gamedata->init())
		{
			return g_gamedata;
		}
	}
	return g_gamedata;
}

bool GameData::init()
{
	this->loadGameConfig();
	this->setGameSpeed(1.0f);
	this->setDefaultGameSpeed(1.0f);
	this->setGameScore(0);
	this->setArmyNum(0);
	this->setGameRunning(true);
	this->setLevel(1);
	this->loadTaskInfo();
	return true;
}

void GameData::setGameSpeed(float speed)
{
	gameSpeed_ = speed;
}

float GameData::getGameSpeed() const
{
	return gameSpeed_;
}

void GameData::resetGameSpeed()
{
	setGameSpeed(originGameSpeed_);
}

void GameData::setGameScore(const float score)
{
	gameScore_ = score;
}

void GameData::addGameScore(const float score)
{
	gameScore_ += score;
}

int GameData::getGameScore() const
{
	return gameScore_;
}

void GameData::resetGameScore()
{
	this->setGameScore(0);
}

void GameData::resetGameData()
{
	this->resetGameScore();
	this->resetGameSpeed();
	this->resetArmyNum();
}

void GameData::loadTaskInfo()
{
	USING_NS_CC;
	taskInfo_ = FileUtils::getInstance()->getValueMapFromFile("Config/Task.plist");

	char name[10];
	sprintf(name, "Level%02d", level_);
	auto nowLevel = taskInfo_[name].asValueMap();
	this->setGameTask(new Task((Task::TYPE)nowLevel["Type"].asInt(), nowLevel["Num"].asInt(), nowLevel["Title"].asString()));

}

void GameData::updateTask()
{
	delete task_;
	char name[10];
	sprintf(name, "Level%02d", level_);
	auto nowLevel = taskInfo_[name].asValueMap();
	this->setGameTask(new Task((Task::TYPE)nowLevel["Type"].asInt(), nowLevel["Num"].asInt(),nowLevel["Title"].asString()));
}

bool GameData::loadLevelInfo(int level)
{
	USING_NS_CC;
	char name[25];
	sprintf(name, "Config/Level%02d.plist", level);
	if (FileUtils::getInstance()->isFileExist(name))
	{
		levelInfo_ = FileUtils::getInstance()->getValueMapFromFile(name);
	}

	auto gameSpeed = levelInfo_["GameSpeed"].asFloat();
	this->setGameSpeed(gameSpeed);
	this->setDefaultGameSpeed(gameSpeed_);
	auto armyInfo = levelInfo_["ArmyInfo"].asValueMap();
	this->setArmyInfo(ArmyInfo::create(armyInfo));
	return true;
}

void GameData::loadGameConfig()
{
	auto info = cocos2d::FileUtils::getInstance()->getValueMapFromFile("Config/GameConfig.plist");
	this->setMaxLevel(info["MaxLevel"].asInt());
}
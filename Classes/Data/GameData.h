#ifndef __GAMEDATA___
#define __GAMEDATA___
#include "Data/Task.h"
#include "Object/Plane.h"
#include "cocos2d.h"
#include "Data/ArmyInfo.h"
class GameData
{
public:
	static GameData* getInstance();

	bool init();

	//game speed
	void setGameSpeed(const float speed);
	void setDefaultGameSpeed(const float speed){ defaultGameSpeed_ = speed; }
	float getDefaultGameSpeed()const { return defaultGameSpeed_; }
	float getGameSpeed() const ;
	void resetGameSpeed();

	//game score
	void setGameScore(const float score);
	void addGameScore(const float score);
	int getGameScore() const;
	void resetGameScore();

	//game task
	void setGameTask(Task* task){ task_ = task; };
	Task* getGameTask() const { return task_; };
	Task::TYPE getTaskType() const { return task_->getTaskType(); }
	std::string getTaskTitle() const { return task_->getTaskTitle(); }
	int getLimitArmyNum() const { return task_->getArmyNum(); }

	void setArmyNum(const int armyNum){ armyNum_ = armyNum; }
	int getArmyNum() const { return armyNum_; }
	void addArmyNum(const int armyNum){ armyNum_ += armyNum; }
	void resetArmyNum() { armyNum_ = 0; }

	//全局量
	Space::HeroPlane* getMainPlane() const { return _mainPlane; }
	void setMainPlane(Space::HeroPlane* plane) { _mainPlane = plane; }
	cocos2d::Sprite* getLeftBtn() const { return _leftBtn; }
	void setLeftBtn(cocos2d::Sprite* btn) { _leftBtn = btn; }
	cocos2d::Sprite* getRightBtn() const { return _rightBtn; }
	void setRightBtn(cocos2d::Sprite* btn) { _rightBtn = btn; }
	cocos2d::Sprite* getFireBtn() const { return _fireBtn; }
	void setFireBtn(cocos2d::Sprite* btn) { _fireBtn = btn; }

	//游戏是否进行
	void setGameRunning(bool flag) { isGameRunning_ = flag; }
	bool isGameRunning() const { return isGameRunning_; }

	//任务信息
	void loadTaskInfo();
	void updateTask();
	//关卡
	bool loadLevelInfo(int level);
	void setLevel(unsigned int level){ level_ = level; }
	void addLevel(unsigned int level){ level_ += level; }
	unsigned int getLevel() const { return level_; }
	void resetLevel(){ this->setLevel(1); }

	//关卡中敌人的配置
	void setArmyInfo(ArmyInfo* info){ armyInfo_ = info; };
	ArmyInfo* getArmyInfo() const { return armyInfo_; }

	//配置
	void loadGameConfig();
	int getMaxLevel() const { return maxLevel_; }
	void setMaxLevel(int level){ maxLevel_ = level; }

	void resetGameData();

private:
	GameData();
	~GameData();

private:
	float originGameSpeed_;
	float defaultGameSpeed_;
	float gameSpeed_;
	int   gameScore_;
	unsigned int level_;
	//超过的敌人个数
	int armyNum_;
	Task* task_;
	Space::HeroPlane* _mainPlane;
	cocos2d::Sprite* _leftBtn;
	cocos2d::Sprite* _rightBtn;
	cocos2d::Sprite* _fireBtn;

	bool isGameRunning_;
	cocos2d::ValueMap taskInfo_;
	cocos2d::ValueMap levelInfo_;

	//最大关卡数
	int maxLevel_;

	//敌人信息
	ArmyInfo* armyInfo_;
};
#endif
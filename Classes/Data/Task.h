#ifndef __TASK___
#define __TASK___
#include <string>
class Task
{
public:
	enum TYPE
	{
		NONE = 0,
		TIME = 1,
		ARMY_NUM = 2
	};

	Task()
	{
		_type = TYPE::NONE;
		armyNum_ = 0;
		lastTime_ = 0.0f;
	}
	Task(TYPE mType, int num, std::string title)
	{
		Task();
		_type = mType;
		armyNum_ = num;
		title_ = title;
	}
	~Task(){}

	static Task* create();
	static Task* createArmyTask(int num);
	static Task* createTimeTask(float time);

	bool initArmyTask(int num);
	bool initTimeTask(float time);
	bool init();

	void setTaskType(TYPE mType){ _type = mType; };
	Task::TYPE getTaskType() const { return _type; }
	int getArmyNum() const { return armyNum_; }
	void setArmyNum(int num){ armyNum_ = num; }

	float getLastTime() const { return lastTime_; }
	void setLastTime(float time){ lastTime_ = time; }

	void setTaskTitle(char* name){ title_ = name; }
	std::string getTaskTitle() const { return title_; }

private:
	Task::TYPE _type;
	int  armyNum_;
	float lastTime_;
	std::string title_;
};
#endif
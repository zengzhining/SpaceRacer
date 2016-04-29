#include "Task.h"
Task* Task::create()
{
	auto task = new Task();
	if (task && task->init())
	{
		return task;
	}
	return nullptr;
}

Task* Task::createArmyTask(int num)
{
	auto task = new Task();
	if (task && task->initArmyTask(num))
	{
		return task;
	}
	return nullptr;
}

Task* Task::createTimeTask(float time)
{
	auto task = new Task();
	if (task && task->initTimeTask(time))
	{
		return task;
	}
	return nullptr;
}

bool Task::init()
{
	return true;
}

bool Task::initArmyTask(int num)
{
	this->setTaskType(TYPE::ARMY_NUM);
	this->setArmyNum(num);
	return true;
}

bool Task::initTimeTask(float time)
{
	this->setTaskType(TYPE::TIME);
	this->setLastTime(time);
	return true;
}





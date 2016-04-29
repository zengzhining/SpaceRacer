#include "Manager/ObjectManager.h"
static ObjectManager* g_objmanager = nullptr;
ObjectManager* ObjectManager::getInstance()
{
	if (g_objmanager == nullptr)
	{
		g_objmanager = new ObjectManager();
		if (g_objmanager && g_objmanager->init())
			return g_objmanager;

	}
	return g_objmanager;
}

bool ObjectManager::init()
{
	//planes_ = std::vector<Space::Plane*>(10);
	return true;
}

void ObjectManager::push(Space::Plane* plane)
{
	plane->retain();
	planes_.push_back(plane);
}

void ObjectManager::clear()
{
	auto planes = this->getPlanes();
	for each (auto plane in planes)
	{
		plane->release();
	}
	while (!planes_.empty())
	{
		planes_.back() = NULL;
		planes_.pop_back();
	}
}

void ObjectManager::destroy()
{
	delete g_objmanager;
	g_objmanager = nullptr;
}
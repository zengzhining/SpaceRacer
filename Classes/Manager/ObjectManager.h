#ifndef __OBJECT_MANAGER___
#define __OBJECT_MANAGER___
#include <vector>
#include "Object/Plane.h"

class ObjectManager
{
public:
	static ObjectManager* getInstance();

	bool init();

	void push(Space::Plane* plane);

	void clear();

	static void destroy();

	std::vector<Space::Plane*>& getPlanes() { return planes_; };

private:
	std::vector<Space::Plane*> planes_;
};
#endif
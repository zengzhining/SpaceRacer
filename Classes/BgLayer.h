#ifndef __BG_LAYER___
#define __BG_LAYER___
#include "cocos2d.h"
USING_NS_CC;
class BgLayer :public Layer
{
public:
	CREATE_FUNC(BgLayer);
	bool init();

	void update(float dt) override;
private:
	Vector<Sprite*> bgSet_;
	int bgIndex_;
};
#endif
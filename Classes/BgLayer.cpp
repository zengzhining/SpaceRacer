#include "BgLayer.h"
#include "Data/GameData.h"
USING_NS_CC;
bool BgLayer::init()
{
	if (!Layer::init())
		return false;
	bgIndex_ = 1;
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB888);
	Director::getInstance()->getTextureCache()->addImageAsync("BackGround/BackGround.png", [this](Texture2D* texture){
		auto size = Director::getInstance()->getVisibleSize();
		for (int i = -1; i <= 1; ++i)
		{
			for (int k = -1; k <= 1; ++k)
			{
				auto bg = Sprite::createWithTexture(texture);
				auto bgSize = bg->getContentSize();
				bg->setPosition(size.width / 2 * (2 *i + 1), size.height /2 * (2 * k + 1)  );
				auto scaleX = size.width / bgSize.width;
				auto scaleY = size.height / bgSize.height;
				bg->setOpacity(0);
				this->addChild(bg);
				bg->setScale(scaleX, scaleY);
				bg->runAction(FadeIn::create(1));
				bgSet_.pushBack(bg);
			}
		}
		scheduleUpdate();



	});


	return true;
}

void BgLayer::update(float dt)
{
	auto size = Director::getInstance()->getVisibleSize();
	//向下滚动
	for (int i = 0; i <= 8;++i)
	{
		auto bg = bgSet_.at(i);
		bg->setPositionY(bg->getPositionY() - 2 * GameData::getInstance()->getGameSpeed());
	}

	for (int i = 0; i <= 8; ++i)
	{
		auto bg = bgSet_.at(i);
		if (bg->getPositionY() < -size.height)
		{
			bg->setPositionY(size.height / 2 * 3);
		}
	}

}

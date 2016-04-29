#ifndef __PLAYER___
#define __PLAYER___
//这里保存玩家数据

class Player
{
public:
	static Player* getInstance();
	void setScore(const float score);
	float getScore() const;
	void addScore(const float score);

	void reset();

private:
	Player();
	~Player();

protected:
	float score_;

};
#endif
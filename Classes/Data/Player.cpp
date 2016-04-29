#include "Player.h"
static Player* g_player = nullptr;
Player::Player()
	:score_(0)
{

}

Player::~Player()
{

}

void Player::reset()
{
	score_ = 0;
}

Player* Player::getInstance()
{
	if (g_player == nullptr)
	{
		g_player = new Player();
		if (g_player)
			return g_player;
	}
	return g_player;
}

void Player::setScore(const float score)
{
	score_ = score;
}

float Player::getScore() const
{
	return score_;
}

void Player::addScore(const float score)
{
	score_ += score;
}


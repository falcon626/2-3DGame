#pragma once

#include"../BaseScene/BaseScene.h"

//class AdminCamera;
class TPVCamera;
class Player;
class LaneManager;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	void AddLane();

	void PreLoad() noexcept override;

	std::weak_ptr<TPVCamera> m_wpCamera;
	std::weak_ptr<Player>    m_wpPlayer;

	float count_i = 16;
	int Delcount_i = -8;
};
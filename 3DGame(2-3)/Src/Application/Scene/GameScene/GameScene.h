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

	void PreLoad() noexcept override;

	std::weak_ptr<TPVCamera> m_wpCamera;
	std::weak_ptr<Player> m_wpPlayer;
	std::shared_ptr<LaneManager> m_spLaneManager;

	bool m_isRightKey = false;
	bool m_isLeftKey = false;
	bool m_isUpKey = false;
	bool m_isDownKey = false;

	float count_i = 18;
	int Delcount_i = -8;
};
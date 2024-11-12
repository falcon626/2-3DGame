#pragma once

#include"../BaseScene/BaseScene.h"

//class AdminCamera;
class TPVCamera;
class Player;
class LaneManager;
class DamageObjects;
class LaneManager;

class GameScene : public BaseScene
{
public :

	GameScene()  {}
	~GameScene() {}

	void Init() override;
private:

	void Event() override;

	void PreLoad() noexcept override;

	std::weak_ptr<TPVCamera>     m_wpCamera;
	std::weak_ptr<Player>        m_wpPlayer;
	std::weak_ptr<DamageObjects> m_wpDamaObjects;

	std::shared_ptr<LaneManager> m_spLaneMana;
};
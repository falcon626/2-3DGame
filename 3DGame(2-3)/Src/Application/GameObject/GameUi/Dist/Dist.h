#pragma once

class Player;
class Counter;

class Dist : public KdGameObject
{
public:
	explicit Dist(const std::weak_ptr<Player>& wp);
	~Dist() override = default;

	void DrawSprite() override;
	void Update() override;
private:
	std::shared_ptr<Counter> m_spCounter;
	std::weak_ptr<Player> m_wpPlayer;

	Math::Vector2 m_pos;

	Math::Vector3 m_playerPos;

	Math::Rectangle m_rect;

	float m_best{};
	bool m_dirty{ false };
};
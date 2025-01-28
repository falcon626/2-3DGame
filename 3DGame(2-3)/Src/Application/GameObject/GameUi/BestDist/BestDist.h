#pragma once

class Player;
class Counter;

class BestDist : public KdGameObject
{
public:
	explicit BestDist(const std::weak_ptr<Player>& wp) noexcept;
	~BestDist() override = default;

	void DrawSprite() override;
	void Update() override;
private:
	std::shared_ptr<KdTexture> m_spTex;
	std::shared_ptr<KdTexture> m_spInequalityTex;

	std::shared_ptr<Counter> m_spCounter;
	std::weak_ptr<Player> m_wpPlayer;

	Math::Vector2 m_pos;

	float m_best{};

	Math::Rectangle m_rect;
};
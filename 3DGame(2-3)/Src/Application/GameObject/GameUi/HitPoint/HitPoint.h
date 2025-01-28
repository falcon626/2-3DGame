#pragma once

class Player;

class HitPoint : public KdGameObject
{
public:
	explicit HitPoint(const std::weak_ptr<Player>& wp);
	~HitPoint() override = default;

	void DrawSprite() override;
	void PreUpdate() override;
	void Update() override;

private:
	inline auto SetPlayer(const std::weak_ptr<Player>& wp) noexcept { m_wpPlayer = wp; }

	std::weak_ptr<Player> m_wpPlayer;
	std::shared_ptr<KdTexture> m_spTex;

	Math::Rectangle m_rect;
	Math::Vector2 m_pos;
	
	uint32_t m_texWide  { Def::UIntZero };
	uint32_t m_texHeight{ Def::UIntZero };

	int32_t m_rectY{ Def::UIntZero };
	int32_t m_oldHitPoint{ 3 };

	float m_motionInterval{ Def::FloatZero };

	bool m_isDame{ false };
};
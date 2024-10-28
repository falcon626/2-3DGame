#pragma once

class Counter;

class Award : public KdGameObject
{
public:
	explicit Award(const Math::Vector3& dist, const int32_t time);
	~Award() override = default;

	void DrawSprite() override;
	void Update()override;

private:
	std::shared_ptr<KdTexture> m_spTex;
	std::shared_ptr<Counter> m_spCounter;

	Math::Vector2 m_pos;

	Math::Vector3 m_oldPos;
	Math::Vector3 m_newPos;

	int32_t m_oldTime{ Def::SizTZero };
	bool m_isMax{ false };
};
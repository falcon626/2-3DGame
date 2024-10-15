#pragma once

class Counter;
class Timer;

class StageTime : public KdGameObject
{
public:
	StageTime();
	~StageTime() override = default;

	void DrawSprite()override;
	void Update();
private:
	std::shared_ptr<KdTexture> m_spTex;

	std::shared_ptr<Counter> m_spCounter;
	std::shared_ptr<Timer>   m_spTimer;

	Math::Vector2            m_pos;

	uint32_t m_time = Def::SizTZero;
};
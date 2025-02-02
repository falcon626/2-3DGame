﻿#pragma once

class Player;

class Counter;
class Timer;

class StageTime : public KdGameObject
{
public:
	explicit StageTime(const std::weak_ptr<Player>& wp);
	~StageTime() override = default;

	void DrawSprite()override;
	void Update();
private:
	std::shared_ptr<KdTexture> m_spTex;

	std::shared_ptr<Counter>   m_spCounter;
	std::shared_ptr<Timer>     m_spTimer;
							  
	std::weak_ptr<Player>      m_wpPlayer;
							  
	Math::Vector2              m_pos;

	Math::Color m_color;

	float m_curveVal{ 360 };

	uint32_t m_time{ Def::UIntZero };
};
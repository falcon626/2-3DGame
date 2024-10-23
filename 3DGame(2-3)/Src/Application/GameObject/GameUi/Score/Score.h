#pragma once

class Counter;

class Score : public KdGameObject
{
public:
	Score();
	~Score() override = default;

	void DrawSprite() override;
private:
	std::shared_ptr<KdTexture> m_spTex;
	std::shared_ptr<Counter> m_spCounter;
};
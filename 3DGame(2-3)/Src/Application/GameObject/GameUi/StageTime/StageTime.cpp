#include "StageTime.h"
#include "../../../System/Counter/Counter.h"
#include "../../../System/Timer/Timer.h"

StageTime::StageTime()
{
	m_spTex = FlDataStorage::Instance().GetTexture("Numbers/numbersBox.png");

	m_spTimer = std::make_shared<Timer>();
	m_spCounter = std::make_shared<Counter>(m_spTex);

	m_pos = { -460,300 };

	m_spTimer->Start();
}

void StageTime::DrawSprite()
{
	m_spCounter->DrawSpriteCounter();
}

void StageTime::Update()
{
	m_time = m_spTimer->ElapsedSeconds();

	m_spCounter->SetCounterParameter(m_time, m_pos);

	m_spCounter->Update();
}

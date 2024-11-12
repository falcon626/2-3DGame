#include "StageTime.h"
#include "../../../System/Counter/Counter.h"
#include "../../../System/Timer/Timer.h"

StageTime::StageTime(const std::weak_ptr<Player>& wp)
{
	m_spTex = FlDataStorage::Instance().GetTexture("Numbers/numbersBox.png");

	m_spTimer = std::make_shared<Timer>();
	m_spCounter = std::make_shared<Counter>(m_spTex);

	m_pos = { -310,200 };

	m_spTimer->Start();

	m_wpPlayer = wp;
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

	if (m_wpPlayer.expired()) m_spTimer->Stop();
}

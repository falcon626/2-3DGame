#include "StageTime.h"
#include "../../../System/Counter/Counter.h"
#include "../../../System/Timer/Timer.h"

#include "../../Player/Player.h"

StageTime::StageTime(const std::weak_ptr<Player>& wp)
{
	m_spTex = FlDataStorage::Instance().GetTexture("Numbers/numbersBox.png");

	m_spTimer = std::make_shared<Timer>();
	m_spCounter = std::make_shared<Counter>(m_spTex);

	m_pos = { -310,200 };

	m_spTimer->Start();

	m_color = Def::Color;

	m_wpPlayer = wp;
}

void StageTime::DrawSprite()
{
	m_spCounter->DrawSpriteCounter();
}

void StageTime::Update()
{
	if (auto sp{ m_wpPlayer.lock() })
	{
		const auto time{ sp->GetLifeTime() };
		if (time <= 10)
		{
			m_color.G(Formula::SinCurve(m_curveVal));
			m_color.B(Formula::SinCurve(m_curveVal));

			m_curveVal = Increment(m_curveVal, 900, m_deltaTime);
			if (m_curveVal >= 360) m_curveVal -= 360;
		}
		else m_color = Def::Color;

		m_spCounter->SetCounterParameter(time, m_pos, m_color);
	}
	else
	{
		m_color = kRedColor;
		m_spCounter->SetCounterParameter(Def::IntZero, m_pos, m_color);
	}
	m_spCounter->Update();
}

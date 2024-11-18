#include "Dist.h"
#include "../../../System/Counter/Counter.h"
#include "../../Player/Player.h"

Dist::Dist(const std::weak_ptr<Player>& wp)
{
	m_spCounter = std::make_shared<Counter>(FlDataStorage::Instance().GetTexture("Numbers/numbers.png"));

	m_wpPlayer = wp;
	m_pos = { -270,300 };

	auto parameter{ std::vector<float>{} };
	auto counter{ Def::UIntZero };

	{
		[[maybe_unused]] const auto IsAssert{ FlResourceAdministrator::Instance().GetBinaryInstance()->Load("Asset/Data/PlayerScore/memory_float.dat", parameter, counter)};
		_ASSERT_EXPR(IsAssert, L"Not Found File");
	}

	m_best = parameter[--counter];
}

void Dist::DrawSprite()
{
	m_spCounter->DrawSpriteCounter();
}

void Dist::Update()
{
	if (auto sp{ m_wpPlayer.lock() })
	{
		m_playerPos = sp->GetPos();

		if (m_playerPos.z > 999)m_playerPos.z = 999;

		m_spCounter->SetCounterParameter(static_cast<const int>(m_playerPos.z), m_pos, { 1,1 - m_playerPos.z / 999,1 - m_playerPos.z / 999,1 });
		
		if (m_best < m_playerPos.z) m_best = m_playerPos.z;
	}
	else if(!m_dirty)
	{
		{
			auto parameter{ std::vector<float>{m_best} };
			[[maybe_unused]] const auto IsAssert{ FlResourceAdministrator::Instance().GetBinaryInstance()->Save("Asset/Data/PlayerScore/memory_float.dat", parameter) };
			_ASSERT_EXPR(IsAssert, L"Not Found File");
		}

		m_dirty = true;
	}

	m_spCounter->Update();
}

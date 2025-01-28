#include "Dist.h"
#include "../../../System/Counter/Counter.h"
#include "../../Player/Player.h"

Dist::Dist(const std::weak_ptr<Player>& wp)
{
	m_spCounter = std::make_shared<Counter>(FlDataStorage::Instance().GetTexture("Numbers/numbers.png"));

	m_wpPlayer = wp;
	m_pos = { -270,300 };

	const auto parameter{ FlResourceAdministrator::Instance().GetBinaryInstance()->LoadData<float>("Asset/Data/PlayerScore/memory_float.dat") };
	auto counter{ parameter->size() };

	m_best = (*parameter)[--counter];
}

void Dist::DrawSprite()
{
	m_spCounter->DrawSpriteCounter();
}

void Dist::Update()
{
	if (auto sp{ m_wpPlayer.lock() })
	{
		auto playerPos{ sp->GetPos() };

		if (playerPos.z > 999)playerPos.z = 999;

		m_spCounter->SetCounterParameter(static_cast<const int>(playerPos.z), m_pos, { 1,1 - playerPos.z / m_best,1 - playerPos.z / m_best,1 });

		if (m_best < playerPos.z)
		{
			m_best  = playerPos.z;
			m_dirty = false;
		}
	}
	else if(!m_dirty)
	{
		{
			auto parameter{ std::vector<float>{m_best} };
			[[maybe_unused]] const auto IsAssert{ FlResourceAdministrator::Instance().GetBinaryInstance()->SaveData("Asset/Data/PlayerScore/memory_float.dat", parameter) };
			_ASSERT_EXPR(IsAssert, L"Not Found File");
		}

		m_dirty = true;
	}

	if (m_wpPlayer.expired())
	{
		m_pos = { 150,50 };
		m_spCounter->SetPos(m_pos);
	}

	m_spCounter->Update();
}

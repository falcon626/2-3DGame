#include "BestDist.h"
#include "../../../System/Counter/Counter.h"

BestDist::BestDist() noexcept
{
	auto parameter{ std::vector<float>{} };
	auto counter{ Def::UIntZero };

	{
		[[maybe_unused]] const auto IsAssert{ BinaryAccessor::Instance().Load("Asset/Data/PlayerScore/memory_float.dat", parameter, counter) };
		_ASSERT_EXPR(IsAssert, L"Not Found File");
	}

	m_best = parameter[--counter];

	m_spCounter = std::make_shared<Counter>(FlDataStorage::Instance().GetTexture("Numbers/numbers.png"));
	m_spTex = FlDataStorage::Instance().GetTexture("Text/best.png");

	m_pos = { -460,300 };
}

void BestDist::DrawSprite()
{
	m_spCounter->DrawSpriteCounter();

	if (!m_spTex) [[unlikely]] return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<const int>(m_pos.x - 55), static_cast<const int>(m_pos.y + 40));
}

void BestDist::Update()
{
	m_spCounter->SetCounterParameter(static_cast<int32_t>(m_best), m_pos, {1,0,0,1});

	m_spCounter->Update();
}

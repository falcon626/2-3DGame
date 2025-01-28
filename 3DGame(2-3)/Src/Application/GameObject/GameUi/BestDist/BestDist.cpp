#include "BestDist.h"
#include "../../../System/Counter/Counter.h"

BestDist::BestDist(const std::weak_ptr<Player>& wp) noexcept
{
	const auto parameter{ FlResourceAdministrator::Instance().GetBinaryInstance()->LoadData<float>("Asset/Data/PlayerScore/memory_float.dat") };
	auto counter{ parameter->size() };

	m_wpPlayer = wp;

	m_best = (*parameter)[--counter];

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
	m_spCounter->SetCounterParameter(static_cast<int32_t>(m_best), m_pos, { 1,0.25f,0.05f,1 });

	m_spCounter->Update();

	if (m_wpPlayer.expired()) m_pos = { -50,50 };
}

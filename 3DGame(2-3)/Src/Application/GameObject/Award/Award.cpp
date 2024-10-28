#include "Award.h"
#include "../../System/Counter/Counter.h"

Award::Award(const Math::Vector3& dist, const int32_t time)
{
	m_spCounter = std::make_shared<Counter>();
	m_spTex = FlDataStorage::Instance().GetTexture("Awardcup/seihai_gold.png");

	auto parameter{ std::vector<float>{} };
	auto counter  { Def::SizTZero };

	{
		[[maybe_unused]] const auto IsAssert{ BinaryAccessor::Instance().Load("Asset/Data/PlayerScore/memory_float.dat", parameter, counter) };
		_ASSERT_EXPR(IsAssert, L"Not Found File");
	}

	m_oldPos.z = parameter[--counter];
	m_newPos = dist;
}

void Award::DrawSprite()
{
	if (!m_spTex) [[unlikely]] return; 

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<const int>(m_pos.x), static_cast<const int>(m_pos.y));
	m_spCounter->DrawSpriteCounter();
}

void Award::Update()
{
	if (m_oldPos.z < m_newPos.z)
	{

	}

	m_spCounter->SetCounterParameter(static_cast<int>(m_oldPos.z), m_pos);
}

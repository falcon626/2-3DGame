#include "HitPoint.h"
#include "../../Player/Player.h"

HitPoint::HitPoint(const std::weak_ptr<Player>& wp)
{
	m_rect  = Math::Rectangle{ 0,m_rectY,150,50 };
	m_spTex = FlDataStorage::Instance().GetTexture("Hp/hitPoint.png");
	m_texWide   = { m_spTex->GetWidth() };
	m_texHeight = { m_spTex->GetHeight() / 4 };
	m_pos       = { -530,200 };

	SetPlayer(wp);
}

void HitPoint::DrawSprite()
{
	if (!m_spTex) [[unlikely]] return; 
	
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<const int>(m_pos.x), static_cast<const int>(m_pos.y),static_cast<const int>(m_texWide), static_cast<const int>(m_texHeight), &m_rect);
}

void HitPoint::PreUpdate()
{
	if (auto sp{ m_wpPlayer.lock() })
	{
		auto playerHitPoint{ sp->GetHp() };

		if (playerHitPoint < m_oldHitPoint)
		{
			m_oldHitPoint = playerHitPoint;

			m_isDame = true;
			m_motionInterval = static_cast<float>(90 / Def::Freame);

			m_rectY += 50;
			m_rect = { 0,m_rectY,150,50 };
		}
		else if (playerHitPoint > m_oldHitPoint)
		{
			m_oldHitPoint = playerHitPoint;

			m_rectY -= 50;
			m_rect = { 0,m_rectY,150,50 };
		}
	}
	else
	{
		m_rect = { 0,150,150,50 };
	}
}

void HitPoint::Update()
{
	if (m_isDame)
	{
		m_pos.x = Formula::Rand(-560.f, -500.f);

		m_motionInterval -= m_deltaTime;

		if (m_motionInterval < Def::IntZero)
		{
			m_motionInterval = Def::FloatZero;
			m_pos.x = -530;
			m_isDame = false;
		}
	}
}

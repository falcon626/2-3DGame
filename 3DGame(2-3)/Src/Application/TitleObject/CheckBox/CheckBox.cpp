﻿#include "CheckBox.h"

CheckBox::CheckBox() noexcept
{
	m_spTex = FlDataStorage::Instance().GetTexture("CheckBox/check.png");

	m_rect = { 0, 0, 48, 48 };
	m_siz = { 50,50 };
}

void CheckBox::DrawSprite()
{
	if (!m_spTex) [[unlikely]] return; 

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, 
		static_cast<const int>(m_pos.x), static_cast<const int>(m_pos.y),
		static_cast<const int>(m_siz.x), static_cast<const int>(m_siz.y), &m_rect);
}

void CheckBox::Update()
{
	if (m_isCheck) m_rect = { 48, 0, 48, 48 };
	else m_rect = { 0, 0, 48, 48 };

}

void CheckBox::Check() noexcept
{
	const auto mouse{ Math::Vector2{static_cast<float>(m_mouse.x),static_cast<float>(m_mouse.y)} };

	if (Formula::GetDistance(m_pos, mouse) <= 40) m_isCheck = !m_isCheck;
}

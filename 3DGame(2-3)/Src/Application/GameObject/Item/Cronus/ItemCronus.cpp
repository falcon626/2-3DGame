#include "ItemCronus.h"

ItemCronus::ItemCronus() noexcept
{
	m_spPolygon = std::make_shared<KdSquarePolygon>(FlDataStorage::Instance().GetTexture("Item/pipo-btleffect212_480.png"));
	m_spPolygon->SetSplit(5, 4);

	m_scale = 0.5f;

	m_spPolygon->SetScale(m_scale);
}

void ItemCronus::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon, m_mWorld);
}

void ItemCronus::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90)) * Math::Matrix::CreateTranslation(m_pos);
}

#pragma once

class BaseBasic2DObject : public KdGameObject
{
public:
	BaseBasic2DObject () noexcept = default;
	virtual ~BaseBasic2DObject() noexcept override = default;

	// Not Virtual Function
	inline void DrawSprite() noexcept override{ if (!m_spTex) [[unlikely]] return; KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<const int>(m_pos.x), static_cast<const int>(m_pos.y)); }

	// Ius Vitae Necisque
	inline auto KillExistence() noexcept { m_isExpired = true; }
protected:

	// KdTexture
	inline auto SetTexturelData(const std::string_view& path) noexcept
	{
		m_spTex = FlDataStorage::Instance().GetTexture(path.data());

		m_texInfo = m_spTex->GetInfo();
	}

	inline auto SetTexScale(const float siz) noexcept  { m_siz = { siz,siz }; }
	inline auto SetTexScale(const Math::Vector2& siz) noexcept { m_siz = siz; }

	// Class Or Struct Value
	D3D11_TEXTURE2D_DESC m_texInfo{};
	Math::Vector2 m_pos;
private:

	// Class Or Struct Value
	std::shared_ptr<KdTexture> m_spTex;
	Math::Vector2 m_siz{ Math::Vector2::One };
};
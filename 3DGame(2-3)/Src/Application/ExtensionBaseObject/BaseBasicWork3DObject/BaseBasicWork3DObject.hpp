#pragma once

class BaseBasicWork3DObject : public KdGameObject
{
public:
	BaseBasicWork3DObject () noexcept = default;
	virtual ~BaseBasicWork3DObject() noexcept override = default;

	// Not Virtual Function
	inline void GenerateDepthMapFromLight() noexcept override { if (!m_spModelWork) [[unlikely]] return; KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld); }
	inline void DrawLit()                   noexcept override { if (!m_spModelWork) [[unlikely]] return; KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld); }

	// Ius Vitae Necisque
	inline auto KillExistence() noexcept { m_isExpired = true; }
protected:
	// KdModelData
	inline auto SetModelData(const std::string_view& path) noexcept{ m_spModelWork = std::make_shared<KdModelWork>(FlDataStorage::Instance().GetModelData(path.data())); }

	inline auto SetCol(const std::string_view& colName, const KdCollider::Type type) noexcept
	{
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape(colName, m_spModelWork, type);
	}

	// Class Or Struct Value
	std::shared_ptr<KdModelWork> m_spModelWork;
	std::shared_ptr<KdAnimator>  m_spAnimator;
};
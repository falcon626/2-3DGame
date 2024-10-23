#pragma once

class BaseBasic3DObject : public KdGameObject
{
public:
	BaseBasic3DObject() noexcept = default;
	virtual ~BaseBasic3DObject() noexcept override = default;

	// Not Virtual Function
	inline void GenerateDepthMapFromLight() noexcept override { if (!m_spModel) [[unlikely]] return; KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld); }
	inline void DrawLit()                   noexcept override { if (!m_spModel) [[unlikely]] return; KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld); }

	// Ius Vitae Necisque
	inline auto KillExistence() noexcept { m_isExpired = true; }
protected:

	// KdModelData
	inline auto SetModelData(const std::string_view& path) noexcept { m_spModel = FlDataStorage::Instance().GetModelData(path.data()); }

	inline auto SetModelData(const std::weak_ptr<KdModelData>& wpModel) noexcept { if (wpModel.expired()) [[unlikely]] return; m_spModel = wpModel.lock(); }

	inline auto SetCol(const std::string_view& colName, const KdCollider::Type type) noexcept
	{
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape(colName, m_spModel, type);
	}
private:

	// Class Or Struct Value
	std::shared_ptr<KdModelData> m_spModel;
};
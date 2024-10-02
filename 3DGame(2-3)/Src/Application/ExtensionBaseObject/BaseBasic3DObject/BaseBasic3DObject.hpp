#pragma once

class BaseBasic3DObject : public KdGameObject
{
public:
	BaseBasic3DObject() noexcept = default;
	virtual ~BaseBasic3DObject() noexcept override = default;

	// Not Virtual Function
	inline void GenerateDepthMapFromLight() noexcept override { KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld); }
	inline void DrawLit()                   noexcept override { KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld); }

	// Ius Vitae Necisque
	inline auto KillExistence() noexcept { m_isExpired = true; }
protected:

	// KdModelData
	inline auto SetModelData(const std::string_view& path) noexcept
	{
		if (path.empty()) return;
		m_spModel = FlDataStorage::Instance().GetModelData(path.data());
	}

	inline auto SetCol(const std::string_view& colName, const KdCollider::Type type) noexcept
	{
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape(colName, m_spModel, type);
	}
private:

	// Class Or Struct Value
	std::shared_ptr<KdModelData> m_spModel;
};
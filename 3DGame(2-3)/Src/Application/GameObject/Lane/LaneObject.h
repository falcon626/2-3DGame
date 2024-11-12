#pragma once

class BaseLaneObj;
class BaseBasic3DObject;

class LaneObject : public KdGameObject
{
public:
	enum class LaneType : uint32_t
	{
		None,
		Ground,
		River,
		Road,
		Rail,
		Max
	};

	explicit LaneObject (const Math::Vector3& pos, const LaneType type) noexcept;
	~LaneObject() noexcept override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void PreUpdate() override;

	inline const auto GetLane() const noexcept { return m_laneObj; }
	inline const auto GetType() const noexcept { return m_type; }

	const bool IsUp() const noexcept;

	// Ius Vitae Necisque
	inline auto KillExistence() noexcept { m_isExpired = true; }

private:
	std::shared_ptr<BaseLaneObj> m_laneObj;

	LaneType m_type;
};
#pragma once

class BaseLaneObj;
class BaseBasic3DObject;

class LaneManager : public KdGameObject
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

	explicit LaneManager (const Math::Vector3& pos, const LaneType type) noexcept;
	LaneManager () noexcept = default;
	~LaneManager() noexcept override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void Update() override;

private:
	// Add ObjctList Function (Emplace_Back)
	template <class T, typename... Args>
	inline auto AddObjList(Args&&... args) noexcept
	{
		static_assert(std::is_base_of<BaseLaneObj, T>::value, "T Must Be Derived From LaneObjTag");
		m_laneObjList.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	std::list<std::shared_ptr<KdGameObject>> m_laneObjList;
};
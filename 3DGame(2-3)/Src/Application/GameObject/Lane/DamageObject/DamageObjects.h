#pragma once

class BaseBasic3DObject;
class LaneObject;

class DamageObjects : public KdGameObject
{
public:
	DamageObjects();
	~DamageObjects() = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;


	inline const auto& GetDamaList() const noexcept { return m_damaObjList; }

private:
	void AddDamaObj();

	void AddCar(const std::shared_ptr<LaneObject>& lane);
	void AddTrain(const std::shared_ptr<LaneObject>& lane);

	void KillDameObj();

	template<typename T>
	struct WeakPtrHash 
	{
		std::size_t operator()(const std::weak_ptr<T>& wp) const noexcept 
		{
			if (auto sp = wp.lock()) return std::hash<std::shared_ptr<T>>{}(sp);
			else return std::hash<const void*>()(nullptr);
		}
	};

	template<typename _T>
	struct WeakPtrEqual 
	{
		bool operator()(const std::weak_ptr<_T>& lhs, const std::weak_ptr<std::type_identity_t<_T>>& rhs) const noexcept {return !lhs.owner_before(rhs) && !rhs.owner_before(lhs);}
	};

	struct DameObjData
	{
		int32_t       interval_ { Def::IntZero };
		Math::Vector3 pos_      { Def::Vec3 };
	};

	std::unordered_map<std::weak_ptr<LaneObject>, DameObjData, WeakPtrHash<LaneObject>, WeakPtrEqual<LaneObject>> m_laneCarDataMap;
	std::unordered_map<std::weak_ptr<LaneObject>, DameObjData, WeakPtrHash<LaneObject>, WeakPtrEqual<LaneObject>> m_laneTrainDataMap;

	std::list<std::shared_ptr<BaseBasic3DObject>> m_damaObjList;
};
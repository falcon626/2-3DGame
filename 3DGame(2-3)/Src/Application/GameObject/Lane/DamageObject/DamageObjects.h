#pragma once

class BaseBasic3DObject;
class LaneObject;
class LaneManager;

class DamageObjects : public KdGameObject
{
public:
	explicit DamageObjects(const std::weak_ptr<LaneManager>& wp);
	~DamageObjects() override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

	inline auto SetTarget(const std::weak_ptr<KdGameObject>& wpTarget) noexcept { m_wpTarget = wpTarget; }

	inline const auto& GetDamaList() const noexcept { return m_damaObjList; }

private:
	void AddDamaObjs() noexcept;

	void AddCar(const std::shared_ptr<LaneObject>& spLaneObj) noexcept;
	void AddTrain(const std::shared_ptr<LaneObject>& spLaneObj) noexcept;

	void KillDameObj() noexcept;

	const std::vector<Math::Matrix> CreateMatrixVector(const std::list<std::shared_ptr<BaseBasic3DObject>>& dameObjs)noexcept;

	// <Functionoid:Custom Hash Functor>
	template<typename T>
	struct WeakPtrHash 
	{
		std::size_t operator()(const std::weak_ptr<T>& wp) const noexcept 
		{
			if (auto sp{ wp.lock() }) return std::hash<std::shared_ptr<T>>{}(sp);
			else return std::hash<const void*>()(nullptr);
		}
	};

	// <Functionoid:Custom Equal Functor>
	template<typename _T>
	struct WeakPtrEqual 
	{
		bool operator()(const std::weak_ptr<_T>& lhs, const std::weak_ptr<std::type_identity_t<_T>>& rhs) const noexcept {return !lhs.owner_before(rhs) && !rhs.owner_before(lhs);}
	};

	typedef struct tagDameObjData
	{
		float	      interval_      { Def::FloatZero };
		Math::Vector3 pos_           { Def::Vec3 };

		const KdCollider::Type Type_ { KdCollider::Type::TypeDamage };
	} DameObjData;

	std::unordered_map<std::weak_ptr<LaneObject>, DameObjData, WeakPtrHash<LaneObject>, WeakPtrEqual<LaneObject>> m_laneCarDataMap;
	std::unordered_map<std::weak_ptr<LaneObject>, DameObjData, WeakPtrHash<LaneObject>, WeakPtrEqual<LaneObject>> m_laneTrainDataMap;

	std::list<std::shared_ptr<BaseBasic3DObject>> m_damaObjList;

	std::weak_ptr<KdGameObject> m_wpTarget;
	std::weak_ptr<LaneManager>  m_wpLaneMana;

	std::shared_ptr<KdModelData> m_spTrain;
	std::shared_ptr<KdModelData> m_spCar;
};

namespace Formula // Convenience Functions
{
	// Simple Rand Function
	[[nodiscard(L"Not Random Return Value")]] decltype(auto) Rand() noexcept
	{
		std::random_device rd;
		std::mt19937 mt{ rd() };

		std::uniform_int_distribution<> dist{ Def::IntZero, RAND_MAX };
		return dist(mt);
	}

	template<typename T> // Rand Function
	[[nodiscard(L"Not Random Return Value")]] decltype(auto) Rand
	(_In_ const T min, _In_ const std::type_identity_t<T> max = { std::numeric_limits<std::type_identity_t<T>>::max() }) noexcept
	{
		std::random_device rd;
		std::mt19937 mt{ rd() };

		if constexpr (std::is_integral<T>::value)
		{
			std::uniform_int_distribution<T> dist{ min, max };
			return dist(mt);
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			std::uniform_real_distribution<T> dist{ min, max };
			return dist(mt);
		}
		else static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Not A Valid Numeric Type");
	}

	template<typename _T> // Rand Function With Exclusion Function
	[[nodiscard(L"Not Random Return Value")]] decltype(auto) Rand
	(_In_ const _T min, _In_ const std::type_identity_t<_T> max, _In_ const std::initializer_list<std::type_identity_t<_T>>& exclusion) noexcept
	{
		std::random_device rd;
		std::mt19937 mt{ rd() };

		// Check Exclusion Function (Lambda)
		auto isExcluded = [&exclusion](const _T& value)
			{ return std::find(exclusion.begin(), exclusion.end(), value) != exclusion.end(); };

		if constexpr (std::is_integral<_T>::value)
		{
			std::uniform_int_distribution<_T> dist{ min, max };
			_T value{};
			do {
				value = dist(mt);
			} while (isExcluded(value));
			return value;
		}
		else if constexpr (std::is_floating_point<_T>::value)
		{
			std::uniform_real_distribution<_T> dist{ min, max };
			_T value{};
			do {
				value = dist(mt);
			} while (isExcluded(value));
			return value;
		}
		else static_assert(std::is_integral<_T>::value || std::is_floating_point<_T>::value, "Not A Valid Numeric Type");
	}

	// Item <Name, Percentage> Return Item Name
	const std::string Lottery(_In_ const std::unordered_map<std::string, double>& items) noexcept
	{
		if (items.empty()) return std::string{ " " };

		// Create CDF
		std::vector<std::pair<std::string, double>> cdf;
		auto cumulative{ Def::DoubleZero };
		for (decltype(auto) item : items)
		{
			cumulative += item.second;
			cdf.emplace_back(item.first, cumulative);
		}

		auto randValue{ Rand(Def::DoubleZero,Def::DoubleOne) };

		// Select Item (Lambda)
		auto it = std::lower_bound(cdf.begin(), cdf.end(), randValue,
			[](const std::pair<std::string, double>& element, double value) 
			{ return element.second < value; });

		return it->first;
	}

	// Items Size == Percentages Size. Return ItemType
	template<typename ItemType, typename PercentageType>
	const auto Lottery(_In_ const std::vector<ItemType>& ids, _In_ const std::vector<PercentageType>& percentages) noexcept
	{
		if (ids.empty() || percentages.empty() || (ids.size() != percentages.size())) return static_cast<ItemType>(nullptr);
		std::unordered_map<ItemType, PercentageType> items;
		for (auto i{Def::UIntZero}; i < ids.size(); ++i)
			items.insert(ids[i], percentages[i]);

		// Create CDF
		std::vector<std::pair<ItemType, PercentageType>> cdf;
		auto cumulative = percentages.empty() ? Def::DoubleZero : percentages[0];
		for (size_t i = 1; i < percentages.size(); ++i)
		{
			cumulative += percentages[i];
			cdf.emplace_back(ids[i], cumulative);
		}

		PercentageType sun{};
		for (const auto& percentage : percentages)
			sun += percentage;

		auto randValue{ Rand<PercentageType>(Def::DoubleZero, sun) };

		// Select Item (Lambda)
		auto it = std::upper_bound(cdf.begin(), cdf.end(), randValue,
			[](const std::pair<ItemType, PercentageType>& element, PercentageType value)
			{ return element.second <= value; });

		return it == cdf.end() ? static_cast<ItemType>(nullptr) : it->first;
	}

	inline namespace Collider // So Deep Nest
	{
		using collider_type = uint32_t;

		typedef union _tagResult 
		{
			struct {
				bool isHit_{ false };
				Math::Vector3 hitPos_{ Def::Vec3 };
			}ray;

			struct {
				bool isHit_{ false };
				Math::Vector3 hitDir_{ Def::Vec3 };
			}sphere;
		}Result, &R_Result;

		// KdGameObject Only Ray Function
		template<class T = KdGameObject>
		auto Ray(_Inout_ R_Result result,
			_In_ const std::list<std::shared_ptr<KdGameObject>>& objList,
			_In_ const Math::Vector3& rayDirection,              _In_ const collider_type& hitType,
			_In_ const Math::Vector3& startPos,                  _In_ const float& rayRange,
			_In_ const Math::Vector3& correctionPos = Def::Vec3, _In_ const float& enableStepHigh = Def::FloatZero,
			_In_ const bool& isSetMaxLength         = false,     _In_ const float& maxLength      = Def::FloatZero,
			_In_opt_ const T& owner = nullptr) noexcept
		{
			KdCollider::RayInfo rayInfo{ hitType, startPos, rayDirection, rayRange + enableStepHigh + correctionPos.y };
			rayInfo.m_pos   += correctionPos;
			rayInfo.m_pos.y += enableStepHigh;
			if (isSetMaxLength && maxLength < rayInfo.m_range) rayInfo.m_range = maxLength;

			result.ray.isHit_  = false;
			result.ray.hitPos_ = Def::Vec3;

			std::list<KdCollider::CollisionResult> retRayList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == owner) continue;
				obj->Intersects(rayInfo, &retRayList);
			}

			auto maxOverLap{ Def::FloatZero };
			for (decltype(auto) ret : retRayList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap         = ret.m_overlapDistance;
					result.ray.isHit_  = true;
					result.ray.hitPos_ = ret.m_hitPos;
				}
			}
		}

		// KdGameObject Only Ray Debug Function
		template<class T = KdGameObject>
		auto Ray(_In_opt_ const std::unique_ptr<KdDebugWireFrame>& upDebug,
			_Inout_ R_Result result,
			_In_ const std::list<std::shared_ptr<KdGameObject>>& objList,
			_In_ const Math::Vector3& rayDirection,              _In_ const collider_type& hitType,
			_In_ const Math::Vector3& startPos,                  _In_ const float& rayRange,
			_In_ const Math::Vector3& correctionPos = Def::Vec3, _In_ const float& enableStepHigh = Def::FloatZero,
			_In_ const bool& isSetMaxLength = false,             _In_ const float& maxLength = Def::FloatZero,
			_In_opt_ const T& owner   = nullptr) noexcept
		{
			KdCollider::RayInfo rayInfo{ hitType, startPos, rayDirection, rayRange + enableStepHigh + correctionPos.y };
			rayInfo.m_pos   += correctionPos;
			rayInfo.m_pos.y += enableStepHigh;
			if (isSetMaxLength && maxLength < rayInfo.m_range) rayInfo.m_range = maxLength;

			result.ray.isHit_  = false;
			result.ray.hitPos_ = Def::Vec3;

			std::list<KdCollider::CollisionResult> retRayList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == owner) continue;
				obj->Intersects(rayInfo, &retRayList);
			}

			auto lineColor{ kGreenColor };

			auto maxOverLap{ Def::FloatZero };
			for (decltype(auto) ret : retRayList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					result.ray.isHit_ = true;
					result.ray.hitPos_ = ret.m_hitPos;
					lineColor = kRedColor;
				}
			}

			if(upDebug) upDebug->AddDebugLine(rayInfo.m_pos, rayInfo.m_range, lineColor);
		}

		// Assignment RayInfo
		auto Ray(_Inout_ KdCollider::RayInfo& rayInfoResult,
			_In_ const Math::Vector3& rayDirection,              _In_ const collider_type& hitType,
			_In_ const Math::Vector3& startPos,                  _In_ const float& rayRange,
			_In_ const Math::Vector3& correctionPos = Def::Vec3, _In_ const float& enableStepHigh = Def::FloatZero) noexcept
		{
			KdCollider::RayInfo rayInfo{ hitType, startPos, rayDirection, rayRange + enableStepHigh + correctionPos.y };
			rayInfo.m_pos   += correctionPos;
			rayInfo.m_pos.y += enableStepHigh;

			rayInfoResult = rayInfo;
		}

		// KdGameObject Only Sphere Function
		template<class _T = KdGameObject>
		static auto Sphere(_Inout_ R_Result result,
			_In_ const std::list<std::shared_ptr<KdGameObject>>& objList,
			_In_ const collider_type& hitType, _In_ const Math::Vector3& centerPos,
			_In_ const float& sphereRadius,    _In_ const Math::Vector3& correctionPos = Def::Vec3,
			_In_opt_ const _T& owner = nullptr) noexcept
		{
			KdCollider::SphereInfo sphereInfo{ hitType,centerPos + correctionPos,sphereRadius };

			result.sphere.isHit_  = false;
			result.sphere.hitDir_ = Def::Vec3;

			std::list<KdCollider::CollisionResult> retSphereList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == owner) continue;
				obj->Intersects(sphereInfo, &retSphereList);
			}

			auto maxOverLap{ Def::FloatZero };
			for (decltype(auto) ret : retSphereList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap            = ret.m_overlapDistance;
					result.sphere.isHit_  = true;
					result.sphere.hitDir_ = ret.m_hitDir;
				}
			}
		}

		// KdGameObject Only Sphere Debug Function
		template<class _T = KdGameObject>
		auto Sphere(_In_opt_ const std::unique_ptr<KdDebugWireFrame>& upDebug,
			_Inout_ R_Result result,
			_In_ const std::list<std::shared_ptr<KdGameObject>>& objList,
			_In_ const collider_type& hitType, _In_ const Math::Vector3& centerPos,
			_In_ const float& sphereRadius,    _In_ const Math::Vector3& correctionPos = Def::Vec3,
			_In_opt_ const _T& owner = nullptr) noexcept
		{
			KdCollider::SphereInfo sphereInfo{ hitType, centerPos + correctionPos, sphereRadius };

			result.sphere.isHit_  = false;
			result.sphere.hitDir_ = Def::Vec3;

			std::list<KdCollider::CollisionResult> retSphereList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == owner) continue;
				obj->Intersects(sphereInfo, &retSphereList);
			}

			auto sphereColor{ kGreenColor };

			auto maxOverLap{ Def::FloatZero };
			for (decltype(auto) ret : retSphereList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap            = ret.m_overlapDistance;
					result.sphere.isHit_  = true;
					result.sphere.hitDir_ = ret.m_hitDir;
					sphereColor           = kRedColor;
				}
			}

			if (upDebug) upDebug->AddDebugSphere(sphereInfo.m_sphere.Center,sphereInfo.m_sphere.Radius,sphereColor);
		}

		// KdGameObject Only Sphere Debug Function
		template<class _T = KdGameObject>
		auto Sphere(_In_ const std::list<std::shared_ptr<KdGameObject>>& objList,
			_In_ const collider_type& hitType, _In_ const Math::Vector3& centerPos,
			_In_ const float& sphereRadius,    _In_ const Math::Vector3& correctionPos = Def::Vec3,
			_In_opt_ const _T& owner = nullptr) noexcept
		{
			KdCollider::SphereInfo sphereInfo{ hitType, centerPos + correctionPos, sphereRadius };

			std::list<KdCollider::CollisionResult> retSphereList;
			for (decltype(auto) obj : objList)
			{
				if (obj.get() == owner) continue;
				obj->Intersects(sphereInfo, &retSphereList);
			}
			
			return retSphereList;
		}
	} // Inline Name Space Collider
} // Name Space Formula
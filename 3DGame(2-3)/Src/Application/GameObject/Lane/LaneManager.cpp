#include "LaneManager.h"
#include "LaneObject.h"
#include "LaneObject/Ground/Ground.h"
#include "../Player/Player.h"
#include "../../Scene/SceneManager.h"

LaneManager::LaneManager(const uint32_t nearNum, const uint32_t tileNum, const uint32_t randMax, const float startPosX, const float initializeLanePosZ) noexcept
	: NearLaneNum	 { nearNum }
	, TileNum		 { tileNum }
	, RandMax		 { randMax }
	, OffsetStartPosX{ startPosX }
	, m_currentIndex { Def::UIntZero }
	, m_laneZ		 { initializeLanePosZ }
{
}

void LaneManager::PreUpdate(const float playerZ)
{
	for (const auto& laneData : m_laneData)
	{
		if (auto sp{ laneData.lock() })
		{
			auto laneZ{ sp->GetPos().z };
			if (laneZ <= playerZ && (playerZ - laneZ) > 10)
			{
				sp->KillExistence();
				AddLane();
			}
			else continue;
		}
		else continue;
	}
}

void LaneManager::Update()
{

}

void LaneManager::AddLane()
{
	auto wpLaneObj{ std::weak_ptr<LaneObject>{} };

	auto isSafe{ static_cast<int>(m_laneZ) % 30};

	if (!isSafe)
	{
		SceneManager::Instance().AddObjListAndWeak<LaneObject>(wpLaneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, m_laneZ), LaneObject::LaneType::River, TileNum, OffsetStartPosX);
	}
	else
	{
		auto rnd{ Formula::Rand(1, 100) };

		if (rnd < 75)
			SceneManager::Instance().AddObjListAndWeak<LaneObject>(wpLaneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, m_laneZ), LaneObject::LaneType::Ground, TileNum, OffsetStartPosX, RandMax);
		else if (rnd < 85)
			SceneManager::Instance().AddObjListAndWeak<LaneObject>(wpLaneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, m_laneZ), LaneObject::LaneType::Road, TileNum, OffsetStartPosX);
		else
			SceneManager::Instance().AddObjListAndWeak<LaneObject>(wpLaneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, m_laneZ), LaneObject::LaneType::Rail, TileNum, OffsetStartPosX);
	}

	AddWeakPtr(wpLaneObj);
}

const std::list<std::shared_ptr<KdGameObject>> LaneManager::GetTilesList(const float playerZ) const
{
	auto nearLanes{ std::vector<std::pair<float, std::shared_ptr<BaseLaneObj>>>{} };

	for (const auto& laneData : m_laneData)
	{
		if (auto sp{ laneData.lock() })
		{
			auto laneZ{ sp->GetPos().z };
			auto dist { std::abs(laneZ - playerZ) };

			nearLanes.emplace_back(dist, sp->GetLane());
		}
	}

	// <Lambda Function:Sort Near Lanes>
	std::sort(nearLanes.begin(), nearLanes.end(), [](const auto& lhs, const auto& rhs) {
		return lhs.first < rhs.first;
		});

	auto top3Lanes{ std::vector<std::shared_ptr<BaseLaneObj>>{} };
	for (auto i{ Def::UIntZero }; i < NearLaneNum && i < nearLanes.size(); ++i)
		top3Lanes.push_back(nearLanes[i].second);

	auto resultList{ std::list<std::shared_ptr<KdGameObject>>{} };

	for (const auto& lane : top3Lanes)
	{
		const auto& tiles = lane->GetTilesList();
		resultList.insert(resultList.end(), tiles.begin(), tiles.end());
	}

	return resultList;
}

void LaneManager::KillLane(const uint32_t element) noexcept
{
	if (auto sp{ m_laneData[element].lock() }) sp->KillExistence();
	else return;
}

void LaneManager::AddWeakPtr(const std::weak_ptr<LaneObject> newElement) noexcept
{
	if (auto sp{ m_laneData[m_currentIndex].lock() }) sp->KillExistence();

	m_laneData[m_currentIndex] = newElement;

	m_wpLastLane = newElement;

	m_currentIndex = (m_currentIndex + Def::UIntOne) % m_laneData.size();
	++m_laneZ;
}

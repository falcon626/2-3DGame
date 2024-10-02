#include "LaneManager.h"
#include "LaneObject.h"
#include "LaneObject/Ground/Ground.h"
#include "../Player/Player.h"
#include "../../Scene/SceneManager.h"

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

	if (Formula::Rand(1, 100) > 50)
		SceneManager::Instance().AddObjListAndWeak<LaneObject>(wpLaneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, m_laneZ), LaneObject::LaneType::Ground);
	else
		SceneManager::Instance().AddObjListAndWeak<LaneObject>(wpLaneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, m_laneZ), LaneObject::LaneType::Road);
	
	AddWeakPtr(wpLaneObj);
}

const std::list<std::shared_ptr<KdGameObject>> LaneManager::GetTilesList(const float playerZ) const
{
	auto nearLane{ Def::FloatOne };
	auto result{ std::shared_ptr<BaseLaneObj>{} };
	for (const auto& laneData : m_laneData)
	{
		if (auto sp{ laneData.lock() })
		{
			auto laneZ{ sp->GetPos().z };

			auto dist{ std::abs(laneZ - playerZ) };

			if (nearLane > dist)
			{
				nearLane = dist;
				result   = sp->GetLane();
			}
			else continue;
		}
		else continue;
	}
	return result->GetTilesList();
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

	m_currentIndex = (m_currentIndex + Def::SizTOne) % m_laneData.size();
	++m_laneZ;
}

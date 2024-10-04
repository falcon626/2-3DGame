#include "DamageObjects.h"
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

#include "../LaneManager.h"
#include "../LaneObject.h"

#include "Car/Car.h"
#include "Train/Train.h"

DamageObjects::DamageObjects()
{
	m_entityId = Id::Enemy;
}

void DamageObjects::GenerateDepthMapFromLight()
{
	for (const auto& dameObj : m_damaObjList)
		dameObj->GenerateDepthMapFromLight();
}

void DamageObjects::DrawLit()
{
	for (const auto& dameObj : m_damaObjList)
		dameObj->DrawLit();
}

void DamageObjects::PreUpdate()
{
	{
		auto it{ m_damaObjList.begin() };

		while (it != m_damaObjList.end())
		{
			if ((*it)->IsExpired()) it = m_damaObjList.erase(it);
			else ++it;
		}
	}

	AddDamaObj();

	for (const auto& dameObj : m_damaObjList)
	{
		dameObj->SetDeltaTime(m_deltaTime);
		dameObj->PreUpdate();
	}
}

void DamageObjects::Update()
{
	for (const auto& dameObj : m_damaObjList)
		dameObj->Update();
}

void DamageObjects::PostUpdate()
{
	for (const auto& dameObj : m_damaObjList)
		dameObj->PostUpdate();

	KillDameObj();
}

void DamageObjects::AddDamaObj()
{
	for (decltype(auto) laneWeakPtr : LaneManager::Instance().GetLaneData())
	{
		if (auto lane = laneWeakPtr.lock())
		{
			AddCar(lane);
			AddTrain(lane);
		}
	}
}

void DamageObjects::AddCar(const std::shared_ptr<LaneObject>& lane)
{
	if (lane->GetType() == LaneObject::LaneType::Road)
	{
		auto& carData = m_laneCarDataMap[lane];

		if (carData.interval_ == Def::IntZero)
		{
			carData.pos_ = lane->GetPos();
			m_damaObjList.emplace_back(std::make_shared<Car>(carData.pos_));

			carData.interval_ = Formula::Rand(120, 410);
		}
		else
		{
			carData.interval_ = static_cast<int32_t>(Decrement(carData.interval_, Def::Freame, m_deltaTime));

			if (carData.interval_ < Def::IntZero) carData.interval_ = Def::IntZero;
		}
	}
}

void DamageObjects::AddTrain(const std::shared_ptr<LaneObject>& lane)
{
	if (lane->GetType() == LaneObject::LaneType::Rail)
	{
		auto& trainData = m_laneTrainDataMap[lane];

		if (trainData.interval_ == Def::IntZero)
		{
			trainData.pos_ = lane->GetPos();
			m_damaObjList.emplace_back(std::make_shared<Train>(trainData.pos_));

			trainData.interval_ = Formula::Rand(160, 410);
		}
		else
		{
			trainData.interval_ = static_cast<int32_t>(Decrement(trainData.interval_, Def::Freame, m_deltaTime));

			if (trainData.interval_ < Def::IntZero) trainData.interval_ = Def::IntZero;
		}
	}
}

void DamageObjects::KillDameObj()
{
	for (const auto& dameObj : m_damaObjList)
		if (8 < dameObj->GetPos().x) dameObj->KillExistence();
}

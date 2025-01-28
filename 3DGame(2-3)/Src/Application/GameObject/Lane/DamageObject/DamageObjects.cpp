#include "DamageObjects.h"
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

#include "../LaneManager.h"
#include "../LaneObject.h"

#include "Car/Car.h"
#include "Train/Train.h"

DamageObjects::DamageObjects(const std::weak_ptr<LaneManager>& wp)
	: m_wpLaneMana(wp)
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

	AddDamaObjs();

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

	auto logger{ std::make_shared<DebugLogger>() };
	DEBUG_LOG(logger, "ゲームエネミー更新");
}

void DamageObjects::PostUpdate()
{
	for (const auto& dameObj : m_damaObjList)
		dameObj->PostUpdate();

	KillDameObj();
}

void DamageObjects::AddDamaObjs() noexcept
{
	if (auto sp{ m_wpLaneMana.lock() })
	{
		// <Repetition:Lane>
		for (decltype(auto) laneWeakPtr : sp->GetLaneData())
		{
			if (auto lane{ laneWeakPtr.lock() })
			{
				AddCar(lane);
				AddTrain(lane);
			}
		}
	}
}

void DamageObjects::AddCar(const std::shared_ptr<LaneObject>& lane) noexcept
{
	if (lane->GetType() != LaneObject::LaneType::Road) return;
	
	auto& carData{ m_laneCarDataMap[lane] };

	if (carData.interval_ == Def::IntZero)
	{
		if(!lane->IsUp()) carData.pos_ = lane->GetPos() + Math::Vector3{ -10,0,0 };
		else carData.pos_ = lane->GetPos() + Math::Vector3{ 4,0,0 };

		m_damaObjList.emplace_back(std::make_shared<Car>(carData.pos_, "CarCol", carData.Type_, lane->IsUp()));

		carData.interval_ =static_cast<float>(Formula::Rand(180, 420) / Def::Freame);
	}
	else
	{
		carData.interval_ -= m_deltaTime;

		if (carData.interval_ < Def::IntZero) carData.interval_ = Def::IntZero;
	}
}

void DamageObjects::AddTrain(const std::shared_ptr<LaneObject>& lane) noexcept
{
	if (lane->GetType() != LaneObject::LaneType::Rail) return;
	
	auto& trainData{ m_laneTrainDataMap[lane] };

	if (trainData.interval_ == Def::IntZero)
	{
		if (!lane->IsUp()) trainData.pos_ = lane->GetPos() + Math::Vector3{ -10,0,0 };
		else trainData.pos_ = lane->GetPos() + Math::Vector3{ 6,0,0 };

		m_damaObjList.emplace_back(std::make_shared<Train>(trainData.pos_, "TrainCol", trainData.Type_, lane->IsUp()));

		trainData.interval_ = static_cast<float>(Formula::Rand(160, 410) / Def::Freame);
	}
	else
	{
		trainData.interval_ -= m_deltaTime;

		if (trainData.interval_ < Def::IntZero) trainData.interval_ = Def::IntZero;
	}
}

void DamageObjects::KillDameObj() noexcept
{
	for (const auto& dameObj : m_damaObjList)
	{
		auto damePos{ dameObj->GetPos() };
		if (15 < damePos.x) dameObj->KillExistence();
	}
}

const std::vector<Math::Matrix> DamageObjects::CreateMatrixVector(const std::list<std::shared_ptr<BaseBasic3DObject>>& dameObjs) noexcept
{
	auto mVec{ std::vector<Math::Matrix>{} };
	mVec.reserve(dameObjs.size());

	for (decltype(auto) dameObj : dameObjs)
		mVec.push_back(dameObj->GetMatrix());

	return mVec;
}

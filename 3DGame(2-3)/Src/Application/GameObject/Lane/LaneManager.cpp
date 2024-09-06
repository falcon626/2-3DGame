#include "LaneManager.h"
#include "../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

#include "LaneObject/Ground/Ground.h"
#include "LaneObject/River/River.h"
#include "LaneObject/Car/Road.h"
#include "LaneObject/Train/Rail.h"

LaneManager::LaneManager(const Math::Vector3& pos, const LaneType type) noexcept
{
	switch (type)
	{
	case LaneType::Ground:
		AddObjList<Ground>(pos);
		break;
	case LaneType::River:
		AddObjList<River>(pos);
		break;
	case LaneType::Road:
		AddObjList<Road>(pos);
		break;
	case LaneType::Rail:
		AddObjList<Rail>(pos);
		break;
	default:
		break;
	}
}

void LaneManager::GenerateDepthMapFromLight()
{
	for (const auto& laneObj : m_laneObjList)
		laneObj->GenerateDepthMapFromLight();
}

void LaneManager::DrawLit()
{
	for (const auto& laneObj : m_laneObjList)
		laneObj->DrawLit();
}

void LaneManager::Update()
{
	for (const auto& laneObj : m_laneObjList)
		laneObj->Update();
}
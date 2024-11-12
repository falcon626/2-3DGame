#include "LaneObject.h"
#include "../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

#include "LaneObject/Ground/Ground.h"
#include "LaneObject/River/River.h"
#include "LaneObject/Road/Road.h"
#include "LaneObject/Rail/Rail.h"

LaneObject::LaneObject(const Math::Vector3& pos, const LaneType type) noexcept
{
	m_entityId = Id::Ground;
	m_mWorld.Translation(pos);

	m_type = type;

	switch (type)
	{
	case LaneType::Ground:
		m_laneObj = std::make_shared<Ground>(pos);
		break;
	case LaneType::River:
		m_laneObj = std::make_shared<River>(pos);
		break;
	case LaneType::Road:
		m_laneObj = std::make_shared<Road>(pos);
		break;
	case LaneType::Rail:
		m_laneObj = std::make_shared<Rail>(pos);
		break;
	default: break;
	}
}

void LaneObject::GenerateDepthMapFromLight()
{
	m_laneObj->GenerateDepthMapFromLight();
}

void LaneObject::DrawLit()
{
	m_laneObj->DrawLit();
}

void LaneObject::PreUpdate()
{
	m_laneObj->PreUpdate();
}

const bool LaneObject::IsUp() const noexcept
{
	return m_laneObj->IsUp();
}

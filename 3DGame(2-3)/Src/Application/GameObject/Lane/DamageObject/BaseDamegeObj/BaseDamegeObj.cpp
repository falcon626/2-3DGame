#include "BaseDamegeObj.h"

BaseDamegeObj::BaseDamegeObj() noexcept
	: m_speed{Def::FloatOne}
	, m_isUp{false}
{}

void BaseDamegeObj::Update()
{
	auto dir{ Def::Vec3 };

	if (m_isUp)dir = Math::Vector3::Left;
	else       dir = Math::Vector3::Right;

	m_pos = MoveLinear(m_pos, dir * m_speed, m_deltaTime);
}

void BaseDamegeObj::PostUpdate()
{
	m_mWorld.Translation(m_pos);
}

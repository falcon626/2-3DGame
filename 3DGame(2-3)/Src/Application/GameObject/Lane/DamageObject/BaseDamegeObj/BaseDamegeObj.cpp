#include "BaseDamegeObj.h"

BaseDamegeObj::BaseDamegeObj() noexcept
	: m_speed{Def::FloatZero}
	, m_isUp{false}
{}

void BaseDamegeObj::Move()
{
	auto dir{ Def::Vec3 };

	if (m_isUp)dir = Math::Vector3::Forward;
	else       dir = Math::Vector3::Backward;

	m_pos = MoveLinear(m_pos, dir * m_speed, m_deltaTime);
}
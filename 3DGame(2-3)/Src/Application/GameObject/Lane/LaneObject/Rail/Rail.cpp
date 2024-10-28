#include "Rail.h"
#include "../CommonTile/CommonTile.hpp"

Rail::Rail(const Math::Vector3& pos) noexcept
{
	if (Formula::Rand(0, 1)) m_isUp = true;

	for (auto i{ Def::SizTZero }; i < 13; ++i)
		AddObjList<CommonTile>("Train/rail1.gltf", Math::Vector3((1 * static_cast<float>(i)) - 8, 0, 0) + pos);
}

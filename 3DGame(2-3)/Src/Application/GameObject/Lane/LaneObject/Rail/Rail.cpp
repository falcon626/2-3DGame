#include "Rail.h"
#include "../CommonTile/CommonTile.hpp"

Rail::Rail(const Math::Vector3& pos, const uint32_t tileNum, const float startPosX) noexcept
{
	if (Formula::Rand(Def::UIntZero, Def::UIntOne)) m_isUp = true;

	for (auto i{ Def::UIntZero }; i < tileNum; ++i)
		AddObjList<CommonTile>("Train/rail1.gltf", Math::Vector3((Def::FloatOne * static_cast<float>(i)) - startPosX, Def::FloatZero, Def::FloatZero) + pos);
}

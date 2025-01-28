#include "River.h"
#include "../CommonTile/CommonTile.hpp"

River::River(const Math::Vector3& pos, const uint32_t tileNum, const float startPosX) noexcept
{
	for (auto i{ Def::UIntZero }; i < tileNum; ++i)
	{
		if (Formula::Rand(Def::UIntZero, 4)) AddObjList<CommonTile>("Terrains/River/river.gltf", Math::Vector3((Def::FloatOne * static_cast<float>(i)) - startPosX, Def::FloatZero, Def::FloatZero) + pos, "HealCol", KdCollider::Type::TypeEvent);
		else AddObjList<CommonTile>("Terrains/River/bridge.gltf", Math::Vector3((Def::FloatOne * static_cast<float>(i)) - startPosX, Def::FloatZero, Def::FloatZero) + pos);
	}
}
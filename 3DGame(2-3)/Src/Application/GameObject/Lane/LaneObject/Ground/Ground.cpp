#include "Ground.h"
#include "../CommonTile/CommonTile.hpp"

Ground::Ground(const Math::Vector3& pos, const uint32_t tileNum, const float startPosX, const uint32_t randMax) noexcept
{
	for (auto i{ Def::UIntZero }; i < tileNum; ++i)
	{
		if (Formula::Rand(Def::UIntZero, randMax)) AddObjList<CommonTile>("Terrains/Terrain/terrain_grass.gltf", Math::Vector3((Def::FloatOne * static_cast<float>(i)) - startPosX, Def::FloatZero, Def::FloatZero) + pos);
		else
		{
			auto path{ std::string{} };
			if (Formula::Rand(Def::UIntZero, Def::UIntOne)) path = "Terrains/Terrain/terrain_treeCOL.gltf";
			else path = "Terrains/Terrain/terrain_tree1COL.gltf";

			AddObjList<CommonTile>(path, Math::Vector3((Def::FloatOne * static_cast<float>(i)) - startPosX, Def::FloatZero, Def::FloatZero) + pos, "TreeCol", KdCollider::Type::TypeBump);
		}
	}
}
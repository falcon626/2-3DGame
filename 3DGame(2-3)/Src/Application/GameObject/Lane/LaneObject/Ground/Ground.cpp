#include "Ground.h"
#include "../CommonTile/CommonTile.hpp"

Ground::Ground(const Math::Vector3& pos) noexcept
{
	for (auto i{ Def::SizTZero }; i < 13; ++i)
	{
		if (i == 8)
		{
			AddObjList<CommonTile>("Terrains/Terrain/terrain_grass.gltf", Math::Vector3((1 * static_cast<float>(i)) - 8, 0, 0) + pos);
			continue;
		}
		if (Formula::Rand(0, 9)) AddObjList<CommonTile>("Terrains/Terrain/terrain_grass.gltf", Math::Vector3((1 * static_cast<float>(i)) - 8, 0, 0) + pos);
		else
		{
			auto path{ std::string{} };
			if (Formula::Rand(0, 1)) path = "Terrains/Terrain/terrain_treeCOL.gltf";
			else path = "Terrains/Terrain/terrain_tree1COL.gltf";

			AddObjList<CommonTile>(path, Math::Vector3((1 * static_cast<float>(i)) - 8, 0, 0) + pos, "TreeCol", KdCollider::Type::TypeBump);
		}
	}
}
#include "Ground.h"
#include "../CommonTile/CommonTile.hpp"

Ground::Ground(const Math::Vector3& pos) noexcept
{
	auto path{ std::string{} };
	for (auto i{ Def::SizTZero }; i < 13; ++i)
	{
		if (Formula::Rand(0, 9)) path = "Terrains/Terrain/terrain_grass.gltf";
		else					 path = "Terrains/Terrain/terrain_tree.gltf";
		AddObjList<CommonTile>(path, Math::Vector3((1 * static_cast<float>(i)) - 8, 0, 0) + pos);
	}
}
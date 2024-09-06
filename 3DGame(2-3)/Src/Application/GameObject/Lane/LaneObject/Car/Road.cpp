#include "Road.h"
#include "../CommonTile/CommonTile.hpp"

Road::Road(const Math::Vector3 pos) noexcept
{
	for (auto i{ Def::SizTZero }; i < 13; ++i)
		AddObjList<CommonTile>("Terrains/Terrain/terrain_road.gltf", Math::Vector3((1 * static_cast<float>(i)) - 8, 0, 0) + pos);
}

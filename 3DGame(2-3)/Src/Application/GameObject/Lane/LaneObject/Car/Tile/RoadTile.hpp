#pragma once
#include "../../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class RoadTile : public BaseBasic3DObject
{
public:
	RoadTile(const Math::Vector3& pos) noexcept
	{
		SetModelData("Terrains/Terrain/terrain_road.gltf");
		SetPos(pos);
	}
};
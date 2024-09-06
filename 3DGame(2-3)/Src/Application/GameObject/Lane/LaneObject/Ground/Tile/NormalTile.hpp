#pragma once
#include "../../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"
#include "../../TileObjTag.hpp"

class NormalTile : public BaseBasic3DObject, TileObjTag
{
public:
	explicit NormalTile(const Math::Vector3& pos) { SetModelData("Terrains/Terrain/terrain_grass.gltf");  SetPos(pos); }
};
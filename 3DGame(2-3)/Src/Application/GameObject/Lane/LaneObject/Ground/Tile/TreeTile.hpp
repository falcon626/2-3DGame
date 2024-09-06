#pragma once
#include "../../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class TreeTile : public BaseBasic3DObject
{
public:
	TreeTile(const Math::Vector3& pos){ SetModelData("Terrains/Terrain/terrain_tree.gltf");  SetPos(pos); }
};
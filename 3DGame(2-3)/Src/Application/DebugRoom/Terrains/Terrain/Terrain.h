#pragma once
// Inheritance
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class Terrain : public BaseBasic3DObject
{
public:
	Terrain() noexcept { SetModelData("Terrains/Terrain/Terrain.gltf"); }
	virtual ~Terrain()		override = default;
};
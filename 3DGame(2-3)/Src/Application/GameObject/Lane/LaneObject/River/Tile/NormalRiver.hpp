#pragma once
#include "../../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"
#include "../../TileObjTag.hpp"

class NormalRiver : public BaseBasic3DObject, TileObjTag
{
public:
	explicit NormalRiver(const Math::Vector3& pos) 
	{ 
		SetModelData("Terrains/River/river.gltf");  
		SetPos(pos); 
	}
};
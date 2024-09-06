#pragma once
#include "../../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class RailTile : public BaseBasic3DObject
{
public:
	RailTile(const Math::Vector3& pos) noexcept 
	{
		SetModelData("Train/rail1.gltf");
		SetPos(pos);
	}
};
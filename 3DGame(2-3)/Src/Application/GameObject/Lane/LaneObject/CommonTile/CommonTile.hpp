#pragma once
#include "../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class CommonTile : public BaseBasic3DObject
{
public:
	explicit CommonTile(const std::string_view path, const Math::Vector3& pos) noexcept { SetModelData(path); SetPos(pos); }
	CommonTile () = default;
	~CommonTile() = default;
};
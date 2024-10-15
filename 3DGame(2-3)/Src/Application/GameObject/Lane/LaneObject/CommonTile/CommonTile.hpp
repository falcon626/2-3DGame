#pragma once
#include "../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class CommonTile : public BaseBasic3DObject
{
public:
	explicit CommonTile(const std::string_view& path, const Math::Vector3& pos)noexcept { SetModelData(path); SetPos(pos); }

	explicit CommonTile(const std::string_view& path, const Math::Vector3& pos, 
		const std::string_view& colName, const KdCollider::Type type) noexcept
	{
		SetModelData(path); 
		SetPos(pos); 
		SetCol(colName, type);
	}

	CommonTile () = default;
	~CommonTile() = default;
};
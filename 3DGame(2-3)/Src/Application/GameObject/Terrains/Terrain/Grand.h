#pragma once
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class Grand : public BaseBasic3DObject
{
public:
	Grand () noexcept = default;
	Grand (const Math::Vector3& pos) noexcept;
	~Grand()noexcept = default;
};
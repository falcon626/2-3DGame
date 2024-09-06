#pragma once
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class Rail : public BaseBasic3DObject
{
public:
	Rail ()noexcept = default;
	Rail (const Math::Vector3& pos)noexcept;
	~Rail()noexcept = default;

private:
};
#pragma once
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class Road : public BaseBasic3DObject
{
public:
	Road() noexcept = default;
	Road(const Math::Vector3 pos) noexcept;
	~Road()noexcept = default;

private:

};
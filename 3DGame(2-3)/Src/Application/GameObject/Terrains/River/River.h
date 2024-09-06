#pragma once
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class River : public BaseBasic3DObject
{
public:
	River() noexcept = default;
	River(const Math::Vector3& pos) noexcept;
	~River()noexcept = default;

private:

};
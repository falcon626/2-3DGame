#pragma once
#include "../BaseLaneObj.h"

class Ground : public BaseLaneObj
{
public:
	explicit Ground(const Math::Vector3& pos) noexcept;
	~Ground()noexcept override = default;
};
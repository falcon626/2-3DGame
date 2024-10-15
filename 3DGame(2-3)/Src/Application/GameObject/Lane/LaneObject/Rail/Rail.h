#pragma once
#include "../BaseLaneObj.h"

class Rail : public BaseLaneObj
{
public:
	explicit Rail(const Math::Vector3& pos)noexcept;
	~Rail()noexcept override = default;
};

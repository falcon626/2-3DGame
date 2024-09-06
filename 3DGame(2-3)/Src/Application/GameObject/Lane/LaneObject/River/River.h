#pragma once
#include "../BaseLaneObj.h"

class River : public BaseLaneObj
{
public:
	explicit River(const Math::Vector3& pos) noexcept;
	River ()noexcept = default;
	~River()noexcept = default;
};
#pragma once
#include "../BaseLaneObj.h"

class River : public BaseLaneObj
{
public:
	explicit River(const Math::Vector3& pos, const uint32_t tileNum, const float startPosX) noexcept;
	~River()noexcept override = default;
};
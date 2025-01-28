#pragma once
#include "../BaseLaneObj.h"

class Ground : public BaseLaneObj
{
public:
	explicit Ground(const Math::Vector3& pos, const uint32_t tileNum, const float startPosX, const uint32_t randMax) noexcept;
	~Ground()noexcept override = default;
};
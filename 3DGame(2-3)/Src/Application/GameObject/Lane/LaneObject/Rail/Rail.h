#pragma once
#include "../BaseLaneObj.h"

class Rail : public BaseLaneObj
{
public:
	explicit Rail(const Math::Vector3& pos, const uint32_t tileNum, const float startPosX)noexcept;
	~Rail()noexcept override = default;
};

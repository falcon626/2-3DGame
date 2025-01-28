#pragma once
#include "../BaseLaneObj.h"

class Road : public BaseLaneObj
{
public:
	explicit Road(const Math::Vector3 pos, const uint32_t tileNum, const float startPosX) noexcept;
	~Road()noexcept override = default;
};
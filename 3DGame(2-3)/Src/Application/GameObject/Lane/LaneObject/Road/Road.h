#pragma once
#include "../BaseLaneObj.h"

class Road : public BaseLaneObj
{
public:
	explicit Road(const Math::Vector3 pos) noexcept;
	~Road()noexcept override = default;
};
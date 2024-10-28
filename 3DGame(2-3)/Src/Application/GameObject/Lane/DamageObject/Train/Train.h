﻿#pragma once
#include "../BaseDamegeObj/BaseDamegeObj.h"

class Train : public BaseDamegeObj
{
public:
	explicit Train(const Math::Vector3& pos, const std::string_view& colName, const KdCollider::Type type, const bool isUp);
	~Train() override = default;

private:

};
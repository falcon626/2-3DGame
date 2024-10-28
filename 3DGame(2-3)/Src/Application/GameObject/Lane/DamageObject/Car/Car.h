#pragma once
#include "../BaseDamegeObj/BaseDamegeObj.h"

class Car : public BaseDamegeObj
{
public:
	explicit Car(const Math::Vector3& pos, const std::string_view& colName, const KdCollider::Type type, const bool isUp);
	~Car() override = default;

private:

};
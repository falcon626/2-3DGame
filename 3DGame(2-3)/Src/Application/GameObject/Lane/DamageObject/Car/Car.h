#pragma once
#include "../BaseDamegeObj/BaseDamegeObj.h"

class Car : public BaseDamegeObj
{
public:
	Car(const Math::Vector3& pos);
	Car() = default;
	~Car() override = default;

private:

};
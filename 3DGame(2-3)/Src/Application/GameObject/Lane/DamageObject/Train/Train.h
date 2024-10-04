#pragma once
#include "../BaseDamegeObj/BaseDamegeObj.h"

class Train : public BaseDamegeObj
{
public:
	Train(const Math::Vector3& pos);
	Train() = default;
	~Train() override = default;

private:

};
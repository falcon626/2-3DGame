#pragma once
#include "../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class Award : public BaseBasic3DObject
{
public:
	explicit Award(const Math::Vector3& dist, const int32_t time);
	~Award() override = default;

private:

};
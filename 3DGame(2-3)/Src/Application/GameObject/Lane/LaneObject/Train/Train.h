#pragma once
#include "../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"
#include "../../../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class Train : public BaseBasic3DObject, BaseMoveObject
{
public:
	Train () noexcept = default;
	Train (const Math::Vector3 pos) noexcept;
	~Train() noexcept = default;

private:

};
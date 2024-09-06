#pragma once
// Inheritance
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"
#include "../../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class WoodenBox : public BaseBasic3DObject, BaseMoveObject
{
public:
	WoodenBox () noexcept { SetModelData("Terrains/WoodenBox/Wooden_Box.gltf"); }
	~WoodenBox() noexcept override = default;

	void Update() override;

	void MovePlusX (bool isMove) noexcept;
	void MoveMinusX(bool isMove) noexcept;
};
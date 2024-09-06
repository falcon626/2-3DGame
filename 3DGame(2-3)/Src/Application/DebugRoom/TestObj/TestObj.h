#pragma once
#include "../../ExtensionBaseObject/BaseBasicWork3DObject/BaseBasicWork3DObject.hpp"
#include "../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class TestObj : public BaseBasicWork3DObject, BaseMoveObject
{
public:
	TestObj() noexcept;
	~TestObj()noexcept = default;

	void PreUpdate()override;
	void Update()override;

	void MovePlusX(bool isMove) noexcept;
	void MoveMinusX(bool isMove) noexcept;
private:
	uint32_t m_count{ Def::SizTZero };
};
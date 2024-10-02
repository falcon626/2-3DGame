#pragma once
#include "../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"
#include "../../../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class BaseDamegeObj : public BaseBasic3DObject, BaseMoveObject
{
public:
	BaseDamegeObj() noexcept;
	virtual ~BaseDamegeObj() override = default;

	void Move();

	void SetPos(const Math::Vector3& pos)noexcept override { SetMemberPos(pos); }
protected:
	float m_speed;
	bool  m_isUp;

private:

};
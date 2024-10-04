#pragma once
#include "../../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"
#include "../../../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class BaseDamegeObj : public BaseBasic3DObject, BaseMoveObject
{
public:
	BaseDamegeObj() noexcept;
	virtual ~BaseDamegeObj() override = default;

	void Update() override;
	void PostUpdate() override;

	inline void SetDeltaTime(const float deltaTime) noexcept override { m_deltaTime = deltaTime; }
	void SetPos(const Math::Vector3& pos)noexcept override { SetMemberPos(pos); }
protected:
	float m_speed;
	bool  m_isUp;

private:

};
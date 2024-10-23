#pragma once
#include "../../ExtensionBaseObject/BaseBasicWork3DObject/BaseBasicWork3DObject.hpp"
#include "../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class TitleFish : public BaseBasicWork3DObject, BaseMoveObject
{
public:
	TitleFish();
	~TitleFish() override = default;

	void PreUpdate() override;
	void Update() override;
private:
	Math::Vector3 m_velocity;

	const float GravityPow = -10.f;
	bool m_isJump{ false };
};
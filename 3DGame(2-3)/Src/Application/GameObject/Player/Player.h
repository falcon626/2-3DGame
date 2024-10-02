#pragma once
#include "../../ExtensionBaseObject/BaseBasicWork3DObject/BaseBasicWork3DObject.hpp"
#include "../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class Player : public BaseBasicWork3DObject, BaseMoveObject
{
public:
	Player () noexcept;
	~Player() noexcept = default;

	void PreUpdate () override;
	void Update    () override;
	void PostUpdate() override;

	void UpdateBumpCol() noexcept;

	void SetPos(const Math::Vector3& pos) noexcept override { SetMemberPos(pos); }

	void MoveRight();
	void MoveLeft ();
	void MoveUp   ();
	void MoveDown ();

	const auto IsMove() const { return m_isMove; }
private:
	Math::Vector3 m_velocity;

	uint32_t m_count    { Def::SizTZero };
	uint32_t m_jumpFream{ Def::SizTZero };

	const float m_rotXrighat = 270;
	const float m_rotXleft   = 90;
	const float m_rotXup     = 180;
	const float m_rotXdown   = 0;
	float m_rotY;
	const float GravityPow = -10.f;
	const float JumpPow    = 1.f;
	float m_gravity = 0.f;

	bool m_isMove = false;
	bool m_isDown = true;
};
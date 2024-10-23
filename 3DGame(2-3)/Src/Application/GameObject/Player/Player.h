#pragma once
#include "../../ExtensionBaseObject/BaseBasicWork3DObject/BaseBasicWork3DObject.hpp"
#include "../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class DamageObjects;
class CameraBase;

class Player : public BaseBasicWork3DObject, BaseMoveObject
{
public:
	Player () noexcept;
	~Player() noexcept override = default;

	void DrawUnLit()  override;

	void PreUpdate () override;
	void Update    () override;
	void PostUpdate() override;

	void SetPos(const Math::Vector3& pos) noexcept override { SetMemberPos(pos); }
	inline auto SetDameObjs(const std::weak_ptr<DamageObjects>& wp) noexcept { m_wpDameObjs = wp; }
	inline auto SetCamera(const std::weak_ptr<CameraBase>& wp) noexcept { m_wpCamera = wp; }
	inline void IsOverLap(const bool isOverLap) noexcept override { m_isOverLap = isOverLap; }

	inline const auto GetHp() const noexcept { return (m_hp <= Def::IntZero) ? Def::IntZero : m_hp; }

	inline const auto IsSafe() const noexcept { return m_isSafe; }

	inline auto IsMinPow(const bool isMinPow) noexcept { m_isMinPow = isMinPow; }

	void MoveRight();
	void MoveLeft ();
	void MoveUp   ();
	void MoveDown ();

	const auto IsMove() const { return m_isMove; }
private:
	void UpdateBumpCol() noexcept;
	void UpdateDameCol() noexcept;
	void UpdateSafeCol() noexcept;

	void UpdateHeal() noexcept;

	std::weak_ptr<DamageObjects> m_wpDameObjs;
	std::weak_ptr<CameraBase>    m_wpCamera;

	Math::Vector3 m_velocity;

	uint32_t m_count    { Def::SizTZero };
	uint32_t m_jumpFream{ Def::SizTZero };

	int32_t m_hp{ Def::IntZero };
	int32_t m_healInterval{ Def::IntZero };
	int32_t m_hitInterval { Def::IntZero };

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

	bool m_isMinPow  = false;
	bool m_isSafe    = false;
	bool m_isOverLap = false;
};
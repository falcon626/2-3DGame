#pragma once
#include "../../ExtensionBaseObject/BaseBasicWork3DObject/BaseBasicWork3DObject.hpp"
#include "../../ExtensionBaseObject/BaseMoveObject/BaseMoveObject.hpp"

class DamageObjects;
class CameraBase;
class LaneManager;
class Timer;

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
	inline auto SetLaneMana(const std::weak_ptr<LaneManager>& wp) noexcept { m_wpLaneMana = wp; }
	inline auto SetMinPow(const bool isMinPow) noexcept { m_isMinPow = isMinPow; }
	inline void SetOverLap(const bool isOverLap) noexcept override { m_isOverLap = isOverLap; }

	inline const auto GetHp() const noexcept { return (m_hp <= Def::IntZero) ? Def::IntZero : m_hp; }
	inline const auto GetLifeTime() const noexcept { return m_lifeTime; }

	inline const auto IsSafe() const noexcept { return m_isSafe; }


	void MoveRight();
	void MoveLeft ();
	void MoveUp   ();
	void MoveDown ();

	const auto IsMove() const noexcept { return m_isMove; }
private:
	void UpdateBumpCol() noexcept;
	void UpdateDameCol() noexcept;
	void UpdateSafeCol() noexcept;

	void UpdateHeal() noexcept;

	std::shared_ptr<Timer>	     m_spTimer;

	std::weak_ptr<DamageObjects> m_wpDameObjs;
	std::weak_ptr<CameraBase>    m_wpCamera;
	std::weak_ptr<LaneManager>   m_wpLaneMana;

	Math::Vector3 m_velocity;

	const Math::Vector3 VelocityZ;
	const Math::Vector3 MinVelocityZ;
	const Math::Vector3 VelocityX;
	const Math::Vector3 MinVelocityX;

	const uint32_t AnimeSpd;
	const uint32_t LifeTimeMax;
	
	const int32_t MaxHp;

	uint32_t m_lifeTime;

	int32_t  m_hp;

	const float RotXleft;
	const float RotXup;
	const float RotXrighat;
	const float RotXdown;
	const float GravityPow;

	const float Reverse;

	float  m_healInterval;
	float  m_hitInterval;

	float m_rotX;

	bool m_isStartTimer;

	bool m_isDown;
	bool m_isMove;

	bool m_isMinPow;
	bool m_isSafe;
	bool m_isOverLap;
};
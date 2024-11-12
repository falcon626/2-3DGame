#include "Player.h"

#include "../Lane/LaneManager.h"
#include "../Lane/LaneObject.h"
#include "../Lane/DamageObject/DamageObjects.h"

#include "../Camera/TPVCamera/TPVCamera.h"

#include "../../Scene/SceneManager.h"
#include "../../main.h"

#include "../../System/Timer/Timer.h"

#include "../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

Player::Player() noexcept
	: VelocityZ     { 0,2,2 }
	, MinVelocityZ  { 0,0.5f,1 }
	, VelocityX     { 2,2,0 }
	, MinVelocityX  { 1,0.5f,0 }
	, AnimeSpd      { 600U }
	, MaxHp         { 3 }
	, m_lifeTime    { Def::UIntZero }
	, m_hp          { Def::IntZero }
	, RotXleft      { 90 }
	, RotXup        { RotXleft + RotXleft }
	, RotXrighat    { RotXup + RotXleft }
	, RotXdown      { Def::FloatZero }
	, GravityPow    { -10.f }
	, Reverse       { -Def::FloatOne }
	, m_healInterval{ Def::FloatZero }
	, m_hitInterval { Def::FloatZero }
	, m_rotX        { Def::FloatZero }
	, m_isDown      { true }
	, m_isMove      { false }
	, m_isMinPow    { false }
	, m_isSafe      { false }
	, m_isOverLap   { false }
{
	SetModelData("Player/fish1.gltf");

	m_entityId = Id::Player;

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModelWork->GetData()->GetAnimation("Swim"));

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_rotX  = RotXup;
	m_pos.y = 0.25f;

	m_hp = MaxHp;
}

void Player::DrawUnLit()
{
	if (!m_spModelWork) [[unlikely]] return;
	if (!m_isOverLap) return;

	KdShaderManager::Instance().ChangeDepthStencilState(KdDepthStencilState::ZDisable);
	KdShaderManager::Instance().m_StandardShader.SetEnableOutLineDraw(true);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);
	KdShaderManager::Instance().ChangeDepthStencilState(KdDepthStencilState::ZEnable);
}

void Player::PreUpdate()
{
	m_spAnimator->AdvanceTime(m_spModelWork->WorkNodes(), Increment(Def::UIntZero, AnimeSpd, m_deltaTime));
	m_spModelWork->CalcNodeMatrices();
}

void Player::Update()
{
	if (m_isMove) 
	{
		m_pos = MoveJump(m_pos, m_velocity, GravityPow, m_deltaTime);

		UpdateBumpCol();

		if (m_pos.y <= 0.3f)
		{
			m_pos.y    = 0.3f;
			m_isMove   = false;
			m_velocity = Def::Vec3;
		}
	}

	auto logger{ std::make_shared<DebugLogger>() };
	DEBUG_LOG(logger, "プレイヤー更新");
}

void Player::PostUpdate()
{
	UpdateDameCol();
	UpdateSafeCol();

	UpdateHeal();

	m_mWorld = Math::Matrix::CreateScale(0.1f) *
		Math::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_rotX),
		Def::FloatZero,
		DirectX::XMConvertToRadians(90)
		) *
		Math::Matrix::CreateTranslation(m_pos);

	if (m_hp == Def::IntZero)KillExistence();
}

void Player::UpdateBumpCol() noexcept
{
	KdCollider::SphereInfo sphere{ KdCollider::TypeBump, m_pos, 0.35f };

	std::list<KdCollider::CollisionResult> retList;

	if (auto sp{ m_wpLaneMana.lock() })
		for (const auto& obj : sp->GetTilesList(m_pos.z))
			obj->Intersects(sphere, &retList);

	auto overlap{ Def::FloatZero };
	auto hit    { false };
	auto normal { Def::Vec3 };

	for (const auto& ret : retList)
	{
		if (overlap < ret.m_overlapDistance)
		{
			hit     = true;
			normal  = ret.m_hitNormal;
			overlap = ret.m_overlapDistance;
		}
	}

	if (hit)
	{
		auto a{ -m_velocity.Dot(normal) };
		auto r{ m_velocity + 2 * a * normal };
		r.Normalize();
		m_velocity = r * 1.5f;

		m_pos += normal * overlap;

		Application::Instance().m_log.AddLog("\nHit\n");
	}

#if _DEBUG
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);
#endif // _DEBUG
}

void Player::UpdateDameCol() noexcept
{
	if (m_hitInterval > Def::FloatZero)
	{
		m_hitInterval = Decrement(m_hitInterval, Def::Freame, m_deltaTime);
		return;
	}

	auto sphere{ KdCollider::SphereInfo{KdCollider::Type::TypeDamage, m_pos, 0.18f} };
	auto retSphereList{ std::list<KdCollider::CollisionResult>{} };

	for (decltype(auto) obj : m_wpDameObjs.lock()->GetDamaList())
		if (obj->Intersects(sphere, &retSphereList))
		{
			--m_hp;
			if (m_hp < Def::IntZero)m_hp = Def::IntZero;

			m_hitInterval = 180;
			Application::Instance().m_log.AddLog("\nDead\n");
		}

#if _DEBUG
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kWhiteColor);
#endif // _DEBUG
}

void Player::UpdateSafeCol() noexcept
{
	auto sphere{ KdCollider::SphereInfo{KdCollider::Type::TypeEvent, m_pos, 0.25f} };
	auto retSphereList{ std::list<KdCollider::CollisionResult>{} };

	if (auto sp{ m_wpLaneMana.lock() })
	{
		for (decltype(auto) obj : sp->GetTilesList(m_pos.z))
		{
			if (obj->Intersects(sphere, &retSphereList))
			{
				m_isSafe = true;
				break;
			}
			else m_isSafe = false;
		}
	}
#if _DEBUG
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kBlueColor);
#endif // _DEBUG
}

void Player::UpdateHeal() noexcept
{
	m_healInterval = Decrement(m_healInterval, Def::Freame, m_deltaTime);
	if (m_healInterval < Def::FloatZero)m_healInterval = Def::FloatZero;

	if (!m_isSafe)return;

	if (m_healInterval <= Def::FloatZero)
	{
		++m_hp;
		if (m_hp > MaxHp) m_hp = MaxHp;
		m_healInterval = 60;

		Application::Instance().m_log.AddLog("\nHeal\n");
	}
}

void Player::MoveRight()
{
	if(m_pos.x > 3.0f || m_isMove)return;
	m_rotX   = RotXrighat;

	if(m_isMinPow) m_velocity = MinVelocityX;
	else m_velocity = VelocityX;
	m_isMove = true;
}

void Player::MoveLeft()
{
	if (m_pos.x < -3.0f || m_isMove)return;
	m_rotX   = RotXleft;

	if (m_isMinPow) m_velocity = MinVelocityX;
	else m_velocity = VelocityX;
	m_velocity.x *= Reverse;
	m_isMove = true;
}

void Player::MoveUp()
{
	if (m_isMove) return;
	m_rotX   = RotXup;

	if (m_isMinPow) m_velocity = MinVelocityZ;
	else
	{
		m_velocity = VelocityZ;
		m_isDown = false;
	}
	m_isMove = true;
}

void Player::MoveDown()
{
	if (m_isDown || m_isMove)return;

	if (auto sp{ m_wpLaneMana.lock() })
	{
		if (auto spLastLane{ sp->GetLastLaneData().lock() })
		{
			auto lastLaneZ{ spLastLane->GetPos().z };

			auto dist{ lastLaneZ - m_pos.z };
			if (dist > 15) return;
		}
	}

	m_rotX     = RotXdown;

	if (m_isMinPow) m_velocity = MinVelocityZ;
	else m_velocity = VelocityZ;
	m_velocity.z *= Reverse;
	m_isMove = true;
	m_isDown = true;
}
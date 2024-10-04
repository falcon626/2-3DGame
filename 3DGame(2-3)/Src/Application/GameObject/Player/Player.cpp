#include "Player.h"
#include "../Lane/LaneManager.h"
#include "../../Scene/SceneManager.h"
#include "../../main.h"

Player::Player() noexcept
	: m_rotY(Def::FloatZero)
{
	SetModelData("Player/fish1.gltf");

	m_entityId = Id::Player;

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModelWork->GetData()->GetAnimation("Swim"));

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_rotY  = m_rotXup;
	m_pos.y = 0.3f;

}

void Player::PreUpdate()
{
	m_spAnimator->AdvanceTime(m_spModelWork->WorkNodes(), Increment(0U, 600U, m_deltaTime));
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
			m_pos.y = 0.3f;
			m_isMove = false;
			m_velocity = Def::Vec3;
		}
	}
}

void Player::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateScale(0.1f) *
		Math::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_rotY),
		DirectX::XMConvertToRadians(0),
		DirectX::XMConvertToRadians(90)
		) *
		Math::Matrix::CreateTranslation(m_pos);
}

void Player::UpdateBumpCol() noexcept
{
	KdCollider::SphereInfo sphere{ KdCollider::TypeBump, m_pos, 0.4f };

	std::list<KdCollider::CollisionResult> retList;
	for (const auto& obj : LaneManager::Instance().GetTilesList(m_pos.z))
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
		m_velocity = r;

		m_pos += normal * overlap;

		Application::Instance().m_log.AddLog("\nHit");
	}

#if _DEBUG
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);
#endif // _DEBUG
}

void Player::MoveRight()
{
	if(m_pos.x > 3.0f || m_isMove)return;
	m_rotY   = m_rotXrighat;
	m_velocity = { 2,2,0 };
	m_isMove = true;
}

void Player::MoveLeft()
{
	if (m_pos.x < -3.0f || m_isMove)return;
	m_rotY   = m_rotXleft;
	m_velocity = { -2,2,0 };
	m_isMove = true;
}

void Player::MoveUp()
{
	if (m_isMove) return;
	m_rotY   = m_rotXup;
	m_velocity = { 0,2,2 };
	m_isMove = true;
	m_isDown = false;
}

void Player::MoveDown()
{
	if (m_isDown || m_isMove)return;
	m_rotY     = m_rotXdown;
	m_velocity = { 0,2,-2 };
	m_isMove = true;
	m_isDown = true;
}
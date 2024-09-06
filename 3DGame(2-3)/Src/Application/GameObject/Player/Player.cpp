#include "Player.h"

Player::Player() noexcept
	: m_rotY(Def::FloatZero)
{
	SetModelData("Player/fish1.gltf");

	m_entityId = Id::Player;

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModelWork->GetData()->GetAnimation("Swim"));

	m_rotY  = m_rotXup;
	m_pos.y = 0.27f;
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

		if (m_pos.y <= 0.27f)
		{
			m_pos.y = 0.27f; 
			m_isMove = false;
			m_velocity = Def::Vec3;
		}
	}
}

void Player::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateScale(0.2f) *
		Math::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_rotY),
		DirectX::XMConvertToRadians(0),
		DirectX::XMConvertToRadians(90)
		) *
		Math::Matrix::CreateTranslation(m_pos);
}

void Player::SetPos(const Math::Vector3& pos)
{
	m_pos = pos;
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
	m_rotY   = m_rotXdown;
	m_velocity = { 0,2,-2 };
	m_isMove = true;
	m_isDown = true;
}
#include "TitleFish.h"

TitleFish::TitleFish()
{
	SetModelData("Player/fish1.gltf");

	m_entityId = Id::Player;

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModelWork->GetData()->GetAnimation("Swim"));

	m_mWorld = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));

	m_pos = { 0,-0.9f,-4.5f };

	SetScale(0.0625f);
	SetPos(m_pos);

	m_velocity = { 0,2,0 };
}

void TitleFish::PreUpdate()
{
	m_spAnimator->AdvanceTime(m_spModelWork->WorkNodes(), Increment(0U, 600U, m_deltaTime));
	m_spModelWork->CalcNodeMatrices();
}

void TitleFish::Update()
{
	if (m_isJump)
	{
		m_pos = MoveJump(m_pos, m_velocity, GravityPow, m_deltaTime);

		if (m_pos.y <= -0.9f)
		{
			m_pos.y = -0.9f;
			m_isJump = false;
			m_velocity = Def::Vec3;
		}
	}

	if (!m_isJump)
	{
		m_isJump = true;
		m_velocity = { 0,2,0 };
	}

	SetPos(m_pos);
}

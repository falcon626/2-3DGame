#include "TestObj.h"
#include "../../main.h"

TestObj::TestObj() noexcept
{
	SetModelData("SkinMeshMan/SkinMeshMan.gltf");

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModelWork->GetData()->GetAnimation("Walk"));

	Application::Instance().m_ImPos.Registration("1", m_pos);
}

void TestObj::PreUpdate()
{
	m_spAnimator->AdvanceTime(m_spModelWork->WorkNodes(), Increment(m_count, Def::Freame, m_deltaTime));
	m_spModelWork->CalcNodeMatrices();

	m_pos = Application::Instance().m_ImPos.Here("1");
}

void TestObj::Update()
{
	SetPos(m_pos);
	Application::Instance().m_ImPos.Registration("1",m_pos);
}


void TestObj::MovePlusX(bool isMove) noexcept
{
	if (!isMove)return;
	m_pos = MoveLinear(GetPos(), { -5,0,0 }, m_deltaTime);
}

void TestObj::MoveMinusX(bool isMove) noexcept
{
	if (!isMove)return;
	m_pos = MoveLinear(GetPos(), { 5,0,0 }, m_deltaTime);
}

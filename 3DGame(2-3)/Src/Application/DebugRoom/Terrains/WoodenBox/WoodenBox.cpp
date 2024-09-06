#include "WoodenBox.h"

void WoodenBox::Update()
{
	SetScale(5.f);
	SetPos(m_pos);
}

void WoodenBox::MovePlusX(bool isMove) noexcept
{
	if (!isMove)return;
	m_pos = MoveLinear(GetPos(), { -5,0,0 }, m_deltaTime);
}

void WoodenBox::MoveMinusX(bool isMove) noexcept
{
	if (!isMove)return;
	m_pos = MoveLinear(GetPos(), { 5,0,0 }, m_deltaTime);
}
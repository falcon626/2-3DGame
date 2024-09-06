#include "Counter.h"

Counter::Counter(const std::shared_ptr<KdTexture>& spTex) noexcept
	: m_oneSize(Def::IntZero)
	, m_computed(Def::IntZero)
	, m_countNumber(Def::IntZero)
{
	Init();
	SetTex(spTex);
}

void Counter::Init()
{
	m_color    = Def::Color;
	m_computed = 10;
}

void Counter::DrawSpriteCounter() noexcept
{
	auto x{ Def::FloatZero };
	for (decltype(auto) digitRect : m_rect)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, static_cast<int>(m_pos.x - (x * digitRect.height)), static_cast<int>(m_pos.y), m_oneSize, m_oneSize, &digitRect, &m_color);
		++x;
	}
}

void Counter::Update() noexcept
{
	SetCounterRect();
}

void Counter::SetCounterParameter(const int& countNumber, const Math::Vector2& pos) noexcept
{
	m_countNumber = countNumber;
	m_pos = pos;
}

void Counter::SetCounterParameter(const int& countNumber, const Math::Vector2& pos, const Math::Color& color) noexcept
{
	m_countNumber = countNumber;
	m_pos = pos;
	m_color = color;
}

void Counter::SetCounterParameter(const int& countNumber, const Math::Vector2& pos, const int& rectSize) noexcept
{
	m_countNumber = countNumber;
	m_pos = pos;
	m_oneSize = rectSize;
}

void Counter::SetCounterParameter(const int& countNumber, const Math::Vector2& pos, const int& rectSize, const Math::Color& color) noexcept
{
	m_countNumber = countNumber;
	m_pos = pos;
	m_oneSize = rectSize;
	m_color = color;
}

void Counter::SetCounterRect() noexcept
{
	auto hundred = m_countNumber / (m_computed * m_computed);
	auto teen = (m_countNumber / m_computed) % m_computed;
	auto one = m_countNumber % m_computed;
	m_rect[static_cast<size_t>(Digit::Hundreds)] = { m_oneSize * hundred, Def::IntZero, m_oneSize, m_oneSize };
	m_rect[static_cast<size_t>(Digit::Tens)]     = { m_oneSize * teen, Def::IntZero, m_oneSize, m_oneSize };
	m_rect[static_cast<size_t>(Digit::Ones)]     = { m_oneSize * one, Def::IntZero, m_oneSize, m_oneSize };
}
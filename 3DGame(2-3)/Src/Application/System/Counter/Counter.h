﻿#pragma once

class Counter
{
public:
	explicit Counter (const std::shared_ptr<KdTexture>& spTex)noexcept;
	~Counter()noexcept = default;

	void DrawSpriteCounter() noexcept;
	void Update() noexcept;
	
	void SetCounterParameter(const int& countNumber, const Math::Vector2& pos) noexcept;
	void SetCounterParameter(const int& countNumber, const Math::Vector2& pos, const Math::Color& color) noexcept;
	void SetCounterParameter(const int& countNumber, const Math::Vector2& pos, const int& rectSize) noexcept;
	void SetCounterParameter(const int& countNumber, const Math::Vector2& pos, const int& rectSize, const Math::Color& color) noexcept;

	inline auto SetPos(const Math::Vector2& pos) noexcept { m_pos = pos; }

private:

	enum class Digit : size_t
	{
		Ones,
		Tens,
		Hundreds,
		Max
	};

	void Init();
	void SetTex(const std::shared_ptr<KdTexture>& spTex) noexcept { m_spTex = spTex; m_oneSize = m_spTex->GetHeight(); }
	void SetCounterRect() noexcept;

	std::array<Math::Rectangle, static_cast<size_t>(Digit::Max)> m_rect;
	std::shared_ptr<KdTexture> m_spTex;
	Math::Vector2 m_pos;
	Math::Color m_color;

	int m_oneSize;
	int m_computed;
	int m_countNumber;
};
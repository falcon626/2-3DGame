#pragma once

class CheckBox : KdGameObject
{
public:
	CheckBox()  noexcept;
	~CheckBox() override = default;

	void DrawSprite() override;

	void SetVec2Pos(const Math::Vector2& pos) noexcept { m_pos = pos; }
	void Check() noexcept;
	inline const auto IsCheck() const noexcept { return m_isCheck; }
private:
	std::shared_ptr<KdTexture> m_spTex;

	Math::Rectangle m_rect;
	Math::Vector2   m_pos;
	bool m_isCheck{ false };
};
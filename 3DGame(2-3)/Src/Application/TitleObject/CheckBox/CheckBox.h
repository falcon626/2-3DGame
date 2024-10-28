#pragma once

class CheckBox : public KdGameObject
{
public:
	CheckBox()  noexcept;
	~CheckBox() override = default;

	void DrawSprite() override;

	void Update() override;

	void SetVec2Pos(const Math::Vector2& pos) noexcept { m_pos = pos; }
	void Check() noexcept;
	inline auto SetCheck(const bool check) noexcept { m_isCheck = check; }
	inline const auto IsCheck() const noexcept { return m_isCheck; }
private:
	std::shared_ptr<KdTexture> m_spTex;

	Math::Rectangle m_rect;
	Math::Vector2   m_pos;
	Math::Vector2   m_siz;
	bool m_isCheck{ false };
};
#pragma once

class CheckBox;

class ModeSelect : public KdGameObject
{
public:
	ModeSelect()  noexcept;
	~ModeSelect() override = default;

	void DrawSprite() override;
	void Update() override;
private:
	std::array<std::shared_ptr<CheckBox>, 8> m_arr;
};
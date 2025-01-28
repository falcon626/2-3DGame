#pragma once

class ItemCronus : public KdGameObject
{
public:
	ItemCronus() noexcept;
	~ItemCronus() override = default;

	void DrawUnLit() override;
	void PostUpdate() override;	
private:
	std::shared_ptr<KdSquarePolygon> m_spPolygon;

	Math::Vector3 m_pos;

	float m_scale;
};
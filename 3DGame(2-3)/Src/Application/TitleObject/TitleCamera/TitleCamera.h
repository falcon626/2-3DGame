#pragma once

class TitleCamera : public KdGameObject
{
public:
	explicit TitleCamera(const Math::Vector3& pos);
	~TitleCamera() override = default;

	void PreDraw()			override;
private:

	std::shared_ptr<KdCamera>	m_spCamera;
};
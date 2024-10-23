#include "TitleCamera.h"

TitleCamera::TitleCamera(const Math::Vector3& pos)
{
	if (!m_spCamera) m_spCamera = std::make_shared<KdCamera>();

	m_mWorld = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(50));
	SetPos(pos);
	m_entityId = Id::Camera;
}

void TitleCamera::PreDraw()
{
	if (!m_spCamera) [[unlikely]] return;

	m_spCamera->SetCameraMatrix(m_mWorld);
	m_spCamera->SetToShader();
}

#include "Rail.h"

Rail::Rail(const Math::Vector3& pos) noexcept
{
	SetModelData("Train/rail1.gltf");
	m_mWorld *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	SetPos(pos);
}
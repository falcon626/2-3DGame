#include "Train.h"

Train::Train(const Math::Vector3& pos, const std::string_view& colName, const KdCollider::Type type, const bool isUp)
{
	m_isUp = isUp;
	if (m_isUp) m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));

	SetModelData("Train/trainCOL1.gltf");
	SetCol(colName, type);

	m_speed = 10.0f;
	SetPos(pos + Math::Vector3{ 0,0.15f,0 });
}

#include "Train.h"

Train::Train(const Math::Vector3& pos, const std::string_view& colName, const KdCollider::Type type)
{
	SetModelData("Train/trainCOL1.gltf");
	SetCol(colName, type);

	m_speed = 10.0f;
	SetPos(pos + Math::Vector3{ 0,0.15f,0 });
}

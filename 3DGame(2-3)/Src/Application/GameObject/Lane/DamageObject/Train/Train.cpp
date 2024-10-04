#include "Train.h"

Train::Train(const Math::Vector3& pos)
{
	SetModelData("Train/trainCOL1.gltf");
	SetScale(1.f);

	m_speed = 10.0f;

	SetPos(pos + Math::Vector3{ 0,0.15f,0 });
}

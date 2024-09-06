#include "Road.h"

Road::Road(const Math::Vector3 pos) noexcept
{
	SetModelData("Terrains/Terrain/terrain_road.gltf");
	m_mWorld *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	SetPos(pos);
}
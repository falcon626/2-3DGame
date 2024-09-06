#include "River.h"

River::River(const Math::Vector3& pos) noexcept
{
	/*if(pos.z<=-Def::FloatOne)*/ SetModelData("Terrains/River/river.gltf");
	m_mWorld *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	SetPos(pos);
}

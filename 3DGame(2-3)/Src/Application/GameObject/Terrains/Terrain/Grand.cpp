#include "Grand.h"

Grand::Grand(const Math::Vector3& pos) noexcept
{
	static int count = 0;
	
	if (count > 40)
	{
		if(Formula::Rand(0,2)>1)
		SetModelData("Terrains/Terrain/terrain_tree1.gltf");
		else
		SetModelData("Terrains/Terrain/terrain_tree2.gltf");
	}
	else SetModelData("Terrains/Terrain/terrain_grass.gltf");
	SetPos(pos);

	m_entityId = Id::Ground;
	++count;
}
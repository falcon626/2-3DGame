#include "Train.h"

Train::Train(const Math::Vector3 pos) noexcept
{
	SetModelData("Train/trainCOL1.gltf");
	SetPos(pos);
}
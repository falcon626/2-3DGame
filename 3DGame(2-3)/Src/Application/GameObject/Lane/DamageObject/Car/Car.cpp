#include "Car.h"

Car::Car(const Math::Vector3& pos)
{
	SetModelData("Car/car1.gltf");
	SetScale(0.5f);

	SetPos(pos + Math::Vector3{ 0,0.15f,0 });
}

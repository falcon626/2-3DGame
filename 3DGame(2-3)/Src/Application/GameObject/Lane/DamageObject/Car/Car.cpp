#include "Car.h"

Car::Car(const Math::Vector3& pos, const std::string_view& colName, const KdCollider::Type type)
{
	SetModelData("Car/car1COL.gltf");
	SetCol(colName, type);

	SetScale(0.5f);
	SetPos(pos + Math::Vector3{ 0,0.15f,0 });
}

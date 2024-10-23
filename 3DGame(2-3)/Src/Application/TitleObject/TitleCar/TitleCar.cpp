#include "TitleCar.h"

TitleCar::TitleCar()
{
	SetModelData("Car/car1.gltf");
	m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90)) * Math::Matrix::CreateScale(0.5f) * Math::Matrix::CreateTranslation({0,-1.2f,-3});
}

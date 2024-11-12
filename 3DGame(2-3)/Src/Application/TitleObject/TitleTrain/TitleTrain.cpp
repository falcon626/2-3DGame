#include "TitleTrain.h"

TitleTrain::TitleTrain()
{
	for (auto i{Def::UIntZero}; i < 25; ++i)
	{
		AddObjList<Tile>("Terrains/Terrain/terrain_road.gltf", Math::Vector3{ 0,-1.2f,-10.f + static_cast<float>(i) });
		AddObjList<Tile>("Terrains/River/river.gltf", Math::Vector3{ 1,-1.2f,-10.f + static_cast<float>(i) });
		AddObjList<Tile>("Terrains/Terrain/terrain_tree.gltf", Math::Vector3{ 2,-1.2f,-10.f + static_cast<float>(i) });
		AddObjList<Tile>("Terrains/Terrain/terrain_grass.gltf", Math::Vector3{ 3,-1.2f,-10.f + static_cast<float>(i) });
		
		auto path{ std::string{"Terrains/Terrain/terrain_tree.gltf"} };
		if (Formula::Rand(0, 1)) path = "Terrains/Terrain/terrain_tree1.gltf";

		AddObjList<Tile>(path, Math::Vector3{ -1,-1.2f,-10.f + static_cast<float>(i) });
		AddObjList<Tile>("Train/rail1.gltf", Math::Vector3{ -2,-1.2f,-10.f + static_cast<float>(i) });
		AddObjList<Tile>("Terrains/Terrain/terrain_grass.gltf", Math::Vector3{ -3,-1.2f,-10.f + static_cast<float>(i) });
	}
}

void TitleTrain::GenerateDepthMapFromLight()
{
	for (const auto& terrain : m_terainList)
		terrain->GenerateDepthMapFromLight();
}

void TitleTrain::DrawLit()
{
	for (const auto& terrain : m_terainList)
		terrain->DrawLit();
}

void TitleTrain::PreUpdate()
{
	auto it{ m_terainList.begin() };

	while (it != m_terainList.end())
	{
		if ((*it)->IsExpired()) it = m_terainList.erase(it);
		else ++it;
	}

	for (const auto& terrain : m_terainList)
		terrain->SetDeltaTime(m_deltaTime);
}

void TitleTrain::Update()
{
	for (const auto& terrain : m_terainList)
		terrain->Update();
}

void TitleTrain::PostUpdate()
{
	for (const auto& terrain : m_terainList)
	{
		auto pos{ terrain->GetPos() };

		if (pos.z > 15.f)
		{
			if (pos.x == 0)		AddObjList<Tile>(terrain->GetPath(), Math::Vector3{ 0,-1.2f,-10.f });
			else if(pos.x == 1) AddObjList<Tile>(terrain->GetPath(), Math::Vector3{ 1,-1.2f,-10.f });
			else				AddObjList<Tile>(terrain->GetPath(), Math::Vector3{ pos.x,-1.2f,-10.f });

			terrain->KillExistence();
		}
	}
}

TitleTrain::Tile::Tile(const std::string_view& path, const Math::Vector3& pos) noexcept
{
	m_path = path;
	SetModelData(m_path);
	m_pos = pos;
	m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
}

void TitleTrain::Tile::Update()
{
	m_pos.z = Increment(m_pos.z, 0.25f, m_deltaTime);

	SetPos(m_pos);
}

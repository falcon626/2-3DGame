#include "BaseLaneObj.h"

void BaseLaneObj::GenerateDepthMapFromLight()
{
	for (const auto& taileObj : m_tilesList)
		taileObj->GenerateDepthMapFromLight();
}

void BaseLaneObj::DrawLit()
{
	for (const auto& taileObj : m_tilesList)
		taileObj->DrawLit();
}

void BaseLaneObj::PreUpdate()
{
	auto it{ m_tilesList.begin() };

	while (it != m_tilesList.end())
	{
		if ((*it)->IsExpired()) it = m_tilesList.erase(it);
		else ++it;
	}
}
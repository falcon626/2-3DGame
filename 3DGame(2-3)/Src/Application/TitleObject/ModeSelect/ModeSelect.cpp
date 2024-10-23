#include "ModeSelect.h"
#include "../CheckBox/CheckBox.h"

ModeSelect::ModeSelect() noexcept
{
	for (auto& arr : m_arr)
		arr = std::make_shared<CheckBox>();
}

void ModeSelect::DrawSprite()
{
	for (const auto& arr : m_arr)
		arr->DrawSprite();
}

void ModeSelect::Update()
{
	for (const auto& arr : m_arr)
	{
		if (arr->IsCheck())
		{
			
		}
	}
}

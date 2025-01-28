#include "ModeSelect.h"
#include "../CheckBox/CheckBox.h"
#include "../../Scene/SceneManager.h"

ModeSelect::ModeSelect() noexcept
{
	for (auto& arr : m_checkBoxArr)
		arr = std::make_shared<CheckBox>();

	m_checkBoxArr[0]->SetVec2Pos({250,200});
	m_checkBoxArr[1]->SetVec2Pos({250,150});
	m_checkBoxArr[2]->SetVec2Pos({250, 50});
	m_checkBoxArr[3]->SetVec2Pos({250,  0});
}

void ModeSelect::DrawSprite()
{
	for (const auto& arr : m_checkBoxArr)
		arr->DrawSprite();
}

void ModeSelect::Update()
{
	auto i{ Def::UIntZero };

	auto mouse{ POINT{} };
	GetCursorPos(&mouse);

	for (const auto& arr : m_checkBoxArr)
	{
		++i;

		arr->SetMousePos(mouse);

		arr->Check();
		if (arr->IsCheck())
		{
			switch (i)
			{
			case 0: SceneManager::Instance().SetMode(SceneManager::Mode::Tuna);
				break;
			case 1: SceneManager::Instance().SetMode(SceneManager::Mode::HardCore);
				break;
			default:
				break;
			}
		}
		arr->Update();
	}
}

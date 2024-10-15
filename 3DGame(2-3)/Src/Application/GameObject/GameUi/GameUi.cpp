#include "GameUi.h"
#include "StageTime/StageTime.h"

GameUi::GameUi()
{
	m_entityId = Id::Ui;

	AddObjList<StageTime>();
}

void GameUi::DrawSprite()
{
	for (const auto& ui : m_uiObjList)
		ui->DrawSprite();
}

void GameUi::Update()
{
	for (const auto& ui : m_uiObjList)
		ui->Update();
}
#include "GameUi.h"
#include "StageTime/StageTime.h"
#include "HitPoint/HitPoint.h"
#include "Dist/Dist.h"

GameUi::GameUi(const std::weak_ptr<Player>& wp)
{
	m_entityId = Id::Ui;

	AddObjList<StageTime>();
	AddObjList<HitPoint>(wp);
	AddObjList<Dist>(wp);
}

void GameUi::DrawSprite()
{
	for (const auto& ui : m_uiObjList)
		ui->DrawSprite();
}

void GameUi::PreUpdate()
{
	for (const auto& ui : m_uiObjList)
		ui->PreUpdate();
}

void GameUi::Update()
{
	for (const auto& ui : m_uiObjList)
	{
		ui->SetDeltaTime(m_deltaTime);
		ui->Update();
	}
}
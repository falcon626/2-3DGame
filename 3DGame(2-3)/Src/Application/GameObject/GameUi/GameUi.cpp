﻿#include "GameUi.h"
#include "StageTime/StageTime.h"
#include "HitPoint/HitPoint.h"
#include "Dist/Dist.h"
#include "BestDist/BestDist.h"

GameUi::GameUi(const std::weak_ptr<Player>& wp)
{
	m_entityId = Id::Ui;

	AddObjList<StageTime>(wp);
	AddObjList<HitPoint>(wp);
	AddObjList<Dist>(wp);
	AddObjList<BestDist>(wp);
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

	auto logger{ std::make_shared<DebugLogger>() };
	DEBUG_LOG(logger, "ゲームUI更新");
}
#include "GameScene.h"
// // // // // Singleton // // // // //
#include "../SceneManager.h"
#include "../../main.h"
//    // // // Inanimate // // //    //
#include "../../GameObject/Lane/LaneObject.h"
#include "../../GameObject/Lane/LaneManager.h"
#include "../../GameObject/Lane/DamageObject/DamageObjects.h"
#include "../../GameObject/GameUi/GameUi.h"
//       // // Creature  // //       //
#include "../../GameObject/Player/Player.h"
//          // Camera    //          //
#include "../../DebugRoom/AdminCamera/AdminCamera.h"
#include "../../GameObject/Camera/TPVCamera/TPVCamera.h"
//             Other                 //
#include "../../System/Console/Console.hpp"

#include "../../GameObject/Item/Cronus/ItemCronus.h"

void GameScene::Event()
{
	if (Key::IsPushingWithFocus(Key::F11)) SceneManager::Instance().SetNextScene(SceneManager::SceneType::Debug);

	if (Key::IsPushingWithFocus(Key::Esc)) SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);

	//if (auto wp{ WeakPtrIsExpired(m_wpCamera) }) wp->SetIsNotCursorFree(Key::IsPushingWithFocus(Key::R_Click));

	if (auto sp{ WeakPtrIsExpired(m_wpPlayer) })
	{
		auto nowWheelVal{ KdWindow::Instance().GetMouseWheelVal() };

		if (Key::IsPushing({ Key::Right, Key::R_Click, Key::D }))			    sp->MoveUp();

		else if (Key::IsPushingWithFocus({ Key::Left,  Key::L_Click, Key::A })) sp->MoveDown();

		else if (Key::IsPushingWithFocus({ Key::Up,    Key::W })) sp->MoveLeft();

		else if (Key::IsPushingWithFocus({ Key::Down,  Key::S })) sp->MoveRight();

		else if (nowWheelVal > Def::IntZero) sp->MoveLeft();

		else if (nowWheelVal < Def::IntZero) sp->MoveRight();

		sp->SetMinPow(Key::IsPushingWithFocus({ Key::Shift, Key::Wheel_Click }));

		m_spLaneMana->PreUpdate(sp->GetPos().z);

		auto logger{ std::make_shared<DebugLogger>() };
		DEBUG_LOG(logger, "ゲームシーン更新");
	}
}

void GameScene::Init()
{
	// Pre Asset Load
	PreLoad();
	
	{
		auto parameter{ FlResourceAdministrator::Instance().
			GetBinaryInstance()->LoadData<float>("Asset/Data/LaneParameter/laneParameter_float.dat") };
		
		if (!parameter)_ASSERT_EXPR(false, "Empty Parameter");
		
		auto counter{ parameter->size()};
		Container::ReverseVector(*parameter);

		const auto nearNum  { static_cast<uint32_t>((*parameter)[--counter]) };
		const auto tileNum  { static_cast<uint32_t>((*parameter)[--counter]) };
		const auto randMax  { static_cast<uint32_t>((*parameter)[--counter]) };
		const auto startPosX{ (*parameter)[--counter] };
		const auto lanePosZ { (*parameter)[--counter] };


		m_spLaneMana = std::make_shared<LaneManager>(nearNum, tileNum, randMax, startPosX, lanePosZ);
	}

	for (auto i{ Def::UIntZero }; i < static_cast<uint32_t>(LaneManager::LaneNumber::Max); ++i)
		m_spLaneMana->AddLane();

	// Add Objects
	AddObjListAndWeak<Player>(m_wpPlayer);

	AddObjList<GameUi>(m_wpPlayer);

	AddObjListAndWeak<DamageObjects>(m_wpDamaObjects, m_spLaneMana);

	//AddObjListAndWeak<AdminCamera>(m_wpCamera);
	AddObjListAndWeak<TPVCamera>(m_wpCamera);
	
	AddObjList<ItemCronus>();

	// Setter
	if (auto sp{ WeakPtrIsExpired(m_wpCamera) })
	{
		sp->SetTarget(m_wpPlayer.lock());
		sp->SetDamageObjcts(m_wpDamaObjects);
	}
	if (auto sp{ WeakPtrIsExpired(m_wpPlayer) })
	{
		sp->SetDameObjs(m_wpDamaObjects);
		sp->SetLaneMana(m_spLaneMana);
	}


	// Debug
	auto logger{ std::make_shared<DebugLogger>()};
	DEBUG_LOG(logger, "ゲームシーン初期化");
}

void GameScene::PreLoad() noexcept
{
	FlDataStorage::Instance().PreLoadData({
		"Numbers/numbers.png",
		"Numbers/numbersBox.png",
		"Train/trainCOL1.gltf"
		});
}
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

void GameScene::Event()
{
	if (Key::IsPushingWithFocus(Key::F11)) SceneManager::Instance().SetNextScene(SceneManager::SceneType::Debug);

	if (Key::IsPushingWithFocus(Key::Esc)) SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);

	//if (auto wp{ WeakPtrIsExpired(m_wpCamera) }) wp->SetIsNotCursorFree(Key::IsPushingWithFocus(Key::R_Click));

	if (auto sp{ WeakPtrIsExpired(m_wpPlayer) })
	{
		auto nowWheelVal{ KdWindow::Instance().GetMouseWheelVal() };

		if (Key::IsPushingWithFocus({ Key::Right, Key::R_Click, Key::D }))      sp->MoveUp();

		else if (Key::IsPushingWithFocus({ Key::Left,  Key::L_Click, Key::A })) sp->MoveDown();

		else if (Key::IsPushingWithFocus({ Key::Up,    Key::W })) sp->MoveLeft();

		else if (Key::IsPushingWithFocus({ Key::Down,  Key::S })) sp->MoveRight();

		else if (nowWheelVal > Def::IntZero) sp->MoveLeft();

		else if (nowWheelVal < Def::IntZero) sp->MoveRight();

		sp->IsMinPow(Key::IsPushingWithFocus({ Key::Shift, Key::Wheel_Click }));

		LaneManager::Instance().PreUpdate(sp->GetPos().z);

		if (Key::IsPushingWithFocus(Key::Tab))
		{
			sp->SetPos({ 0,0.25f,0 });
		}
	}
	else if (m_wpPlayer.expired())
	{

	}
	if (Key::IsPushing(Key::P))
	{
		LaneManager::Instance().KillLane(0);
		LaneManager::Instance().KillLane(1);
		LaneManager::Instance().KillLane(2);
		LaneManager::Instance().KillLane(3);
		LaneManager::Instance().KillLane(4);
		LaneManager::Instance().KillLane(5);
		LaneManager::Instance().KillLane(6);
		LaneManager::Instance().KillLane(7);
		LaneManager::Instance().KillLane(8);
	}
}

void GameScene::Init()
{
	// Pre Asset Load
	PreLoad();

	// Add Objects
	AddObjListAndWeak<Player>(m_wpPlayer);

	AddObjList<GameUi>(m_wpPlayer);

	AddObjListAndWeak<DamageObjects>(m_wpDamaObjects);

	AddLane();

	//AddObjListInitAndWeak<AdminCamera>(m_wpCamera);
	AddObjListAndWeak<TPVCamera>(m_wpCamera);

	// Setter
	if (auto sp{ WeakPtrIsExpired(m_wpCamera) })
	{
		sp->SetTarget(m_wpPlayer.lock());
		sp->SetDamageObjcts(m_wpDamaObjects);
	}
	if (auto sp{ WeakPtrIsExpired(m_wpPlayer) })
	{
		sp->SetDameObjs(m_wpDamaObjects);
	}
}

void GameScene::PreLoad() noexcept
{
	FlDataStorage::Instance().PreLoadData({
		"Player/fish1.gltf",
		"Numbers/numbersBox.png"
		});
}

void GameScene::AddLane()
{
	std::initializer_list<LaneObject::LaneType> lanes{
		LaneObject::LaneType::Rail,
		LaneObject::LaneType::Rail,
		LaneObject::LaneType::Road,
		LaneObject::LaneType::River,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::River,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::River,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Rail,
		LaneObject::LaneType::Road,
		LaneObject::LaneType::Road,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Rail,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Ground,
		LaneObject::LaneType::Rail,
		LaneObject::LaneType::Rail,
		LaneObject::LaneType::River,
	};

	auto laneObj{ std::weak_ptr<LaneObject>{} };

	auto z{ -9.f };

	for(const auto& lane : lanes)
	{
		AddObjListAndWeak<LaneObject>(laneObj, Math::Vector3(Def::FloatZero, Def::FloatZero, z), lane);
		LaneManager::Instance().AddWeakPtr(laneObj);
		++z;
	}
}
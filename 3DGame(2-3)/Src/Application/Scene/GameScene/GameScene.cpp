#include "GameScene.h"
// // // // // Singleton // // // // //
#include "../SceneManager.h"
#include "../../main.h"
//    // // // Inanimate // // //    //
#include "../../GameObject/Lane/LaneManager.h"
//       // // Creature  // //       //
#include "../../GameObject/Player/Player.h"
//          // Camera    //          //
#include "../../DebugRoom/AdminCamera/AdminCamera.h"
#include "../../GameObject/Camera/TPVCamera/TPVCamera.h"
//             Other                 //

void GameScene::Event()
{
	if (Key::IsPushingWithFocus(Key::F11)) SceneManager::Instance().SetNextScene(SceneManager::SceneType::Debug);

	//if (auto wp{ WeakPtrIsExpired(m_wpCamera) }) wp->SetIsNotCursorFree(Key::IsPushingWithFocus(Key::R_Click));

	if (auto wp{ WeakPtrIsExpired(m_wpPlayer) })
	{
		if (Key::IsPushingWithFocus(Key::Right))
		{
			if (!m_isRightKey)
			{
				wp->MoveUp();
				if (Formula::Rand(0, 99) < 70)
				{
					AddObjList<LaneManager>(Math::Vector3(0, 0, count_i), LaneManager::LaneType::Ground);
				}
				else
				{
					auto ran{ Formula::Rand(0,99) };
					if (ran < 40)
					{
						AddObjList<LaneManager>(Math::Vector3(0, 0, count_i), LaneManager::LaneType::Rail);
					}
					else
					{
						AddObjList<LaneManager>(Math::Vector3(0, count_i, 13), LaneManager::LaneType::Road);
					}
				}
				++count_i;
			}
			m_isRightKey = true;
		}
		else m_isRightKey = false;

		if (Key::IsPushingWithFocus(Key::Left))
		{
			if (!m_isLeftKey)
			{
				wp->MoveDown();
			}
			m_isLeftKey = true;
		}
		else m_isLeftKey = false;

		if (Key::IsPushingWithFocus(Key::Up))
		{
			if (!m_isUpKey)
			{
				wp->MoveLeft();
			}
			m_isUpKey = true;
		}
		else m_isUpKey = false;

		if (Key::IsPushingWithFocus(Key::Down))
		{
			if (!m_isDownKey)
			{
				wp->MoveRight();
			}
			m_isDownKey = true;
		}
		else m_isDownKey = false;
	
		if (Key::IsPushingWithFocus(Key::Enter))
		{
			wp->SetPos({ 0,0.25f,0 });
		}
	}
}

void GameScene::Init()
{
	// Pre Asset Load
	PreLoad();

	// Add Objects
	AddObjList<LaneManager>(Def::Vec3,LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,-1), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,-3), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,-4), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,-5), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,3), LaneManager::LaneType::River);
	AddObjList<LaneManager>(Math::Vector3(0,0,4), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,5), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,9), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,11), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,15), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,16), LaneManager::LaneType::Ground);
	AddObjList<LaneManager>(Math::Vector3(0,0,1), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,-8), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,10), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,12), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,13), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,6), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,14), LaneManager::LaneType::Rail);
	AddObjList<LaneManager>(Math::Vector3(0,0,2), LaneManager::LaneType::Road);
	AddObjList<LaneManager>(Math::Vector3(0,0,-7), LaneManager::LaneType::Road);
	AddObjList<LaneManager>(Math::Vector3(0,0,7), LaneManager::LaneType::Road);
	AddObjList<LaneManager>(Math::Vector3(0,0,8), LaneManager::LaneType::Road);
	AddObjList<LaneManager>(Math::Vector3(0,0,13), LaneManager::LaneType::Road);
	AddObjList<LaneManager>(Math::Vector3(0,0,17), LaneManager::LaneType::Road);
	AddObjList<LaneManager>(Math::Vector3(0,0,-2), LaneManager::LaneType::River);
	AddObjList<LaneManager>(Math::Vector3(0,0,-6), LaneManager::LaneType::River);

	AddObjListAndWeak<Player>(m_wpPlayer);

	//AddObjListInitAndWeak<AdminCamera>(m_wpCamera);
	AddObjListInitAndWeak<TPVCamera>(m_wpCamera);
	// Setter
	if (auto wp{ WeakPtrIsExpired(m_wpCamera) }) wp->SetTarget(m_wpPlayer.lock());
}

void GameScene::PreLoad() noexcept
{
	FlDataStorage::Instance().PreLoadData({
		"Player/fish1.gltf",
		"Numbers/numbersBox.png"
		});
}
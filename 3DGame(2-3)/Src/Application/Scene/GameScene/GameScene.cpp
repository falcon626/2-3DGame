#include "GameScene.h"
// // // // // Singleton // // // // //
#include "../SceneManager.h"
#include "../../main.h"
//    // // // Inanimate // // //    //
#include "../../GameObject/Lane/LaneObject.h"
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
					AddObjList<LaneObject>(Math::Vector3(0, 0, count_i), LaneObject::LaneType::Ground);
				}
				else
				{
					auto ran{ Formula::Rand(0,99) };
					if (ran < 40)
					{
						AddObjList<LaneObject>(Math::Vector3(0, 0, count_i), LaneObject::LaneType::Rail);
					}
					else
					{
						AddObjList<LaneObject>(Math::Vector3(0, count_i, 13), LaneObject::LaneType::Road);
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
	AddObjList<LaneObject>(Def::Vec3,LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,-1), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,-3), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,-4), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,-5), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,3), LaneObject::LaneType::River);
	AddObjList<LaneObject>(Math::Vector3(0,0,4), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,5), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,9), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,11), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,15), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,16), LaneObject::LaneType::Ground);
	AddObjList<LaneObject>(Math::Vector3(0,0,1), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,-8), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,10), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,12), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,13), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,6), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,14), LaneObject::LaneType::Rail);
	AddObjList<LaneObject>(Math::Vector3(0,0,2), LaneObject::LaneType::Road);
	AddObjList<LaneObject>(Math::Vector3(0,0,-7), LaneObject::LaneType::Road);
	AddObjList<LaneObject>(Math::Vector3(0,0,7), LaneObject::LaneType::Road);
	AddObjList<LaneObject>(Math::Vector3(0,0,8), LaneObject::LaneType::Road);
	AddObjList<LaneObject>(Math::Vector3(0,0,13), LaneObject::LaneType::Road);
	AddObjList<LaneObject>(Math::Vector3(0,0,17), LaneObject::LaneType::Road);
	AddObjList<LaneObject>(Math::Vector3(0,0,-2), LaneObject::LaneType::River);
	AddObjList<LaneObject>(Math::Vector3(0,0,-6), LaneObject::LaneType::River);

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
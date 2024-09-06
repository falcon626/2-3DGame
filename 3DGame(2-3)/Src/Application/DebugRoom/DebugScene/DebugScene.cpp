#include "DebugScene.h"
// // // // // Singleton // // // // //
#include "../../Scene/SceneManager.h"
#include "../../main.h"
//#include "../../System/Console/Console.hpp"
//    // // // Inanimate // // //    //
#include "../Terrains/Terrain/Terrain.h"
#include "../Terrains/WoodenBox/WoodenBox.h"
#include "../TestObj/TestObj.h"
//       // // Creature  // //       //

//          // Camera    //          //
#include "../AdminCamera/AdminCamera.h"
//             Other                 //

void DebugScene::Event()
{
	if (auto wp{ WeakPtrIsExpired(m_wpCamera) }) wp->SetIsNotCursorFree(Key::IsPushingWithFocus(Key::R_Click));

	if (auto wp{ WeakPtrIsExpired(m_wpBox) })
	{
		wp->MovePlusX(Key::IsPushingWithFocus(Key::A));
		wp->MoveMinusX(Key::IsPushingWithFocus(Key::D));
	}

	if (auto wp{ WeakPtrIsExpired(m_wpTest) })
	{
		wp->MovePlusX(Key::IsPushingWithFocus(Key::W));
		wp->MoveMinusX(Key::IsPushingWithFocus(Key::S));
	}

	if (Key::IsPushingWithFocus(Key::F12)) SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
}

void DebugScene::Init()
{
	// Pre Asset Load
	PreLoad();

	// Add Objects
	AddObjList<Terrain>();
	AddObjListAndWeak<TestObj>(m_wpTest);
	AddObjListAndWeak<WoodenBox>(m_wpBox);

	AddObjListInitAndWeak<AdminCamera>(m_wpCamera);

	// Setter

	// Debug
	static_assert(noexcept(AddObjList<Terrain>()), "AddObjList<Terrain> Function");
	static_assert(noexcept(AddObjListAndWeak<TestObj>(m_wpTest)), "AddObjListAndWeak<TestObj> Function");
	static_assert(noexcept(AddObjListAndWeak<WoodenBox>(m_wpBox)), "AddObjListAndWeak<WoodenBox> Function");
	static_assert(noexcept(AddObjListInitAndWeak<AdminCamera>(m_wpCamera)), "AddObjListInitAndWeak<AdminCamera> Function");

	static_assert(noexcept(WeakPtrIsExpired(m_wpCamera)), "WeakPtrIsExpired Function");
	static_assert(noexcept(WeakPtrIsExpired(m_wpBox)), "WeakPtrIsExpired Function");
	static_assert(noexcept(WeakPtrIsExpired(m_wpTest)), "WeakPtrIsExpired Function");
}

void DebugScene::PreLoad() noexcept
{
	FlDataStorage::Instance().PreLoadData({
		"Terrains/Terrain/Terrain.gltf",
		"Terrains/WoodenBox/Wooden_Box.gltf",
		"SkinMeshMan/SkinMeshMan.gltf",
		});
}
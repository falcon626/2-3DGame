#include "TitleScene.h"
#include "../SceneManager.h"

#include "../../TitleObject/TitleCamera/TitleCamera.h"

#include "../../TitleObject/Bar/Bar.h"
#include "../../TitleObject/TitleCar/TitleCar.h"
#include "../../TitleObject/TitleTrain/TitleTrain.h"
#include "../../TitleObject/TitleFish/TitleFish.h"
#include "../../TitleObject/ModeSelect/ModeSelect.h"

void TitleScene::Event()
{
	if (Key::IsPushingWithFocus({ Key::Wheel_Click, Key::Enter, Key::Space }))
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	//auto nowWheelVal{ KdWindow::Instance().GetMouseWheelVal() };

	//if (nowWheelVal > Def::SizTZero)
	//{

	//}
	//else if (nowWheelVal < Def::SizTZero)
	//{

	//}
}

void TitleScene::Init()
{
	AddObjList<TitleCamera>(Math::Vector3{0,0,-4.8f});
	AddObjList<Bar>();
	AddObjList<TitleCar>();
	AddObjList<TitleTrain>();
	AddObjList<TitleFish>();
	// AddObjList<ModeSelect>();
}

#pragma once
#include "../../ExtensionBaseObject/BaseBasic2DObject/BaseBasic2DObject.hpp"

class GameUi : public BaseBasic2DObject
{
public:
	GameUi () noexcept = default;
	~GameUi() noexcept = default;

	void Update()override;
private:
	std::list<std::shared_ptr<KdGameObject>> m_uiObjList;
};
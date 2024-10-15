#pragma once
#include "../../ExtensionBaseObject/BaseBasic2DObject/BaseBasic2DObject.hpp"

class GameUi : public KdGameObject
{
public:
	GameUi ();
	~GameUi() noexcept = default;

	void DrawSprite()override;
	void Update()override;
private:
	template <class T, typename... Args>
	inline auto AddObjList(Args&&... args) noexcept
	{
		static_assert(std::is_base_of<KdGameObject, T>::value, "T Must Be Derived From KdGameObject");
		m_uiObjList.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	std::list<std::shared_ptr<KdGameObject>> m_uiObjList;
};
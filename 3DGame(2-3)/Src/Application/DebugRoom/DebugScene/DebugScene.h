#pragma once

#include "../../Scene/BaseScene/BaseScene.h"


class AdminCamera;
class WoodenBox;
class TestObj;

class DebugScene : public BaseScene
{
public:
	DebugScene() { Init(); }
	~DebugScene(){}

private:
	void Event() override;
	void Init() override;

	void PreLoad() noexcept override;


	std::weak_ptr<AdminCamera> m_wpCamera;
	std::weak_ptr<WoodenBox> m_wpBox;
	std::weak_ptr<TestObj> m_wpTest;
};
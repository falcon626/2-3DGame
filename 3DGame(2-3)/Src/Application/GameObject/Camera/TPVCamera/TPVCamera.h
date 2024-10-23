#pragma once
#include "../CameraBase.h"

class DamageObjects;

class TPVCamera : public CameraBase
{
public:
	TPVCamera()           {}
	~TPVCamera() override {}

	void Init()				;
	void PostUpdate()		override;

	inline auto SetDamageObjcts(const std::weak_ptr<DamageObjects>& wp) noexcept { m_wpDameObjs = wp; }
private:
	const bool IsInterrupt() noexcept;

	std::weak_ptr<DamageObjects> m_wpDameObjs;

	bool m_isInterrupt = false;
};
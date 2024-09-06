#pragma once
#include "../../GameObject/Camera/CameraBase.h"

class AdminCamera : public CameraBase
{
public:
	AdminCamera () noexcept = default;
	~AdminCamera() noexcept override = default;

	void Init()				override;
	void PostUpdate()		override;

	auto SetIsNotCursorFree(const bool& isNotCursorFree) noexcept { m_isNotCursorFree = isNotCursorFree; }
private:
	bool m_isNotCursorFree   = false;
	bool m_isSetCenterCursor = false;
};
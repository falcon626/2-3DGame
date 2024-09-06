#pragma once
#include "../CameraBase.h"

class TPVCamera : public CameraBase
{
public:
	TPVCamera()           {}
	~TPVCamera() override {}

	void Init()				override;
	void PostUpdate()		override;

	void PreventFilling(const std::shared_ptr<const KdGameObject>& spTarget) noexcept;
};
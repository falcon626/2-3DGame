#pragma once
#include "../CameraBase.h"

class CCTVCamera : public CameraBase
{
public:
	CCTVCamera ()noexcept = default;
	~CCTVCamera()noexcept = default;

	void Init()				;
	void PostUpdate()		override;
private:

	void UpdateLookAtRotate(const Math::Vector3& tagetPos);
};
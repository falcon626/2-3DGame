﻿#pragma once
#include "../CameraBase.h"

class FPSCamera : public CameraBase
{
public:
	FPSCamera()							{}
	~FPSCamera()			override	{}

	void Init()				;
	void PostUpdate()		override;
};
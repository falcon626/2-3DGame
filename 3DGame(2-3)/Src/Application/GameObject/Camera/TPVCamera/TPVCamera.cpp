#include "TPVCamera.h"
#include "../../Player/Player.h"
#include "../../Lane/DamageObject/DamageObjects.h"
#include "../../../Scene/SceneManager.h"
#include "../../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

void TPVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45)) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(270));
	m_mLocalPos = m_mRotation * Math::Matrix::CreateTranslation(4.5f, 3.5f, 3.f);
}

void TPVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	auto							    _targetMat { Def::Mat };
	const std::shared_ptr<KdGameObject> _spTarget  { m_wpTarget.lock() };
	if (_spTarget)
	{
		Math::Vector3 pos{ 0,0,_spTarget->GetPos().z };
		_targetMat = Math::Matrix::CreateTranslation(pos);

		_spTarget->SetOverLap(IsInterrupt());

		// カメラの回転
		m_mWorld = m_mLocalPos * _targetMat;
	}

	auto logger{ std::make_shared<DebugLogger>() };
	DEBUG_LOG(logger, "ゲームカメラ更新");
}

const bool TPVCamera::IsInterrupt() noexcept
{
	if (m_wpDameObjs.expired() || m_wpTarget.expired())return false;

	m_isInterrupt = true;

	auto spDame{ m_wpDameObjs.lock() };
	auto spCamera{ m_wpTarget.lock() };

	auto pos{ GetPos() + Math::Vector3{0,2.5f,0} };

	auto dir{ spCamera->GetPos() - pos };
	auto range{ dir.LengthSquared() };

	auto ray{ KdCollider::RayInfo{KdCollider::Type::TypeDamage, pos, dir, range} };
	auto retRayList{ std::list<KdCollider::CollisionResult>{} };

	for (decltype(auto) obj : spDame->GetDamaList())
		if (obj->Intersects(ray, &retRayList)) return true;
	return false;
}

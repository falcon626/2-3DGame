#include "TPSCamera.h"

void TPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();
	if (!!_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld	= m_mLocalPos * m_mRotation * _targetMat;

	// カメラめり込み制御
	PreventFilling(_spTarget);
}

void TPSCamera::PreventFilling(const std::shared_ptr<const KdGameObject>& spTarget) noexcept
{
	KdCollider::RayInfo _rayInfo;
	const auto _nowPos{ GetPos() };


	_rayInfo.m_pos  = _nowPos;
	_rayInfo.m_type = KdCollider::Type::TypeGround;

	if (!!spTarget)
	{
		auto _tagPos     = spTarget->GetPos();
		_tagPos.y       += 0.1f;
		_rayInfo.m_dir   = _tagPos - _nowPos;
		_rayInfo.m_range = _rayInfo.m_dir.Length();
		_rayInfo.m_dir.Normalize();
	}
	else
	{
		_rayInfo.m_dir   = Math::Vector3::Down;
		_rayInfo.m_range = 1000.0f;
	}

	for (auto& _wpGameObj : m_wpHitObjectList)
	{
		auto _spGameObj{ _wpGameObj.lock() };
		if (!!_spGameObj)
		{
			std::list<KdCollider::CollisionResult> _rayResult;
			_spGameObj->Intersects(_rayInfo, &_rayResult);

			auto _maxOveLap{ Def::FloatZero };
			auto _hitPos   { Def::Vec3 };
			auto _isHit    { false };

			for (const auto& _ret : _rayResult)
			{
				if (_maxOveLap < _ret.m_overlapDistance)
				{
					_maxOveLap = _ret.m_overlapDistance;
					_hitPos    = _ret.m_hitPos;
					_isHit     = true;
				}
			}

			if (_isHit)
			{
				auto _corrPos{ _hitPos };
				_corrPos     += _rayInfo.m_dir * 0.4f;
				SetPos(_corrPos);
			}
		}
	}
}
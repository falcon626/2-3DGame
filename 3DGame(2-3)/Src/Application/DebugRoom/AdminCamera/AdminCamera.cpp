#include "AdminCamera.h"

void AdminCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.0f);
}

void AdminCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget  = m_wpTarget.lock();
	if (!!_spTarget) _targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());

	// カメラの回転
	if (m_isNotCursorFree)
	{
		if (!m_isSetCenterCursor)
		{
			m_isSetCenterCursor = true;
			SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
		}
		UpdateRotateByMouse();
	}
	else m_isSetCenterCursor = false;
	m_mRotation = GetRotationMatrix();
	m_mWorld    = m_mLocalPos * m_mRotation * _targetMat;
}

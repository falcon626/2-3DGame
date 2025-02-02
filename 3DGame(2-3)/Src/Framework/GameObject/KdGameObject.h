﻿#pragma once

// ゲーム上に存在するすべてのオブジェクトの基底となるクラス
class KdGameObject : public std::enable_shared_from_this<KdGameObject>
{
public:

	enum class [[maybe_unused]] Id : size_t
	{
		UnKnown        [[maybe_unused]] = Def::BitMaskPos0,
															  
		BackGround     [[maybe_unused]] = Def::BitMaskPos1  << Def::HalfBit,
		Ground         [[maybe_unused]] = Def::BitMaskPos2  << Def::HalfBit,
		Obstacle       [[maybe_unused]] = Def::BitMaskPos3  << Def::HalfBit,
		OtherInanimate [[maybe_unused]] = Def::BitMaskPos4  << Def::HalfBit,

		Ui			   [[maybe_unused]] = Def::BitMaskPos5 << Def::HalfBit,
														    
		Effect         [[maybe_unused]] = Def::BitMaskPos6  << Def::HalfBit,
		Enemy          [[maybe_unused]] = Def::BitMaskPos7  << Def::HalfBit,
		Player         [[maybe_unused]] = Def::BitMaskPos8  << Def::HalfBit,
		OtherCreature  [[maybe_unused]] = Def::BitMaskPos9  << Def::HalfBit,
															   
		Camera         [[maybe_unused]] = Def::BitMaskPos10 << Def::HalfBit,
	};

	// どのような描画を行うのかを設定するTypeID：Bitフラグで複数指定可能
	enum
	{
		eDrawTypeLit           = Def::BitMaskPos1,
		eDrawTypeUnLit         = Def::BitMaskPos2,
		eDrawTypeBright        = Def::BitMaskPos3,
		eDrawTypeUI            = Def::BitMaskPos4,
		eDrawTypeDepthOfShadow = Def::BitMaskPos5,
	};

	KdGameObject() {}
	virtual ~KdGameObject() { Release(); }

	// 生成される全てに共通するパラメータに対する初期化のみ
	//virtual void Init() {}

	virtual void PreUpdate() {}
	virtual void Update() {}
	virtual void PostUpdate() {}

	// それぞれの状況で描画する関数
	virtual void GenerateDepthMapFromLight() {}
	virtual void PreDraw() {}
	virtual void DrawLit() {}
	virtual void DrawUnLit() {}
	virtual void DrawBright() {}
	virtual void DrawSprite() {}

	virtual void DrawDebug();

	virtual void SetAsset(const std::string&) {}

	virtual void SetPos(const Math::Vector3& pos) { m_mWorld.Translation(pos); }
	virtual Math::Vector3 GetPos() const { return m_mWorld.Translation(); }

	// Entity Id Getter
	inline const auto GetEntityId() const noexcept { return m_entityId; }

	inline const auto IdFilter(Id id, size_t filterMask) noexcept { return (static_cast<size_t>(id) & filterMask) != Def::UIntZero; }

	virtual void OnHit()                                    {}
	virtual void OnHit(const int  ) {}
	virtual void OnHit(const float) {}

	// 拡大率を変更する関数
	void SetScale(float scalar);
	virtual void SetScale(const Math::Vector3& scale);
	virtual Math::Vector3 GetScale() const;

	const Math::Matrix& GetMatrix() const { return m_mWorld; }

	virtual bool IsExpired() const { return m_isExpired; }

	virtual bool IsVisible()	const { return false; }
	virtual bool IsRideable()	const { return false; }

	virtual inline void SetOverLap(const bool) noexcept {};

	// 視錐台範囲内に入っているかどうか
	virtual bool CheckInScreen(const DirectX::BoundingFrustum&) const { return false; }

	// カメラからの距離を計算
	virtual void CalcDistSqrFromCamera(const Math::Vector3& camPos);

	float GetDistSqrFromCamera() const { return m_distSqrFromCamera; }

	UINT GetDrawType() const { return m_drawType; }

	bool Intersects(const KdCollider::SphereInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults);
	bool Intersects(const KdCollider::BoxInfo& targetBox, std::list<KdCollider::CollisionResult>* pResults);
	bool Intersects(const KdCollider::RayInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults);

	virtual inline void SetDeltaTime(const float deltaTime) noexcept { m_deltaTime = deltaTime; }

protected:

	void Release() {}

	template <typename T>
	inline const auto Increment(const T value, const std::type_identity_t<T> incrementRate, const float deltaTime) noexcept
	{
		static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Not A Valid Numeric Type");

		auto newValue = value + incrementRate * deltaTime;

		return newValue;
	}

	inline const auto Increment(const auto incrementRate, const float deltaTime) noexcept { return incrementRate * deltaTime; }

	template <typename _T>
	inline const auto Decrement(const _T value, const std::type_identity_t<_T> decrementRate, const float deltaTime) noexcept
	{
		static_assert(std::is_integral<_T>::value || std::is_floating_point<_T>::value, "Not A Valid Numeric Type");

		auto newValue = value - decrementRate * deltaTime;

		return newValue;
	}

	inline const auto Decrement(const auto decrementRate, const float deltaTime) noexcept { return decrementRate * deltaTime; }

	float m_deltaTime{ Def::FloatZero };

	// 描画タイプ・何の描画を行うのかを決める / 最適な描画リスト作成用
	UINT m_drawType = 0;

	// カメラからの距離
	float m_distSqrFromCamera = 0;

	// 存在消滅フラグ
	bool m_isExpired = false;

	// 3D空間に存在する機能
	Math::Matrix	m_mWorld;

	// 当たり判定クラス
	std::unique_ptr<KdCollider> m_pCollider = nullptr;

	// デバッグ情報クラス
	std::unique_ptr<KdDebugWireFrame> m_pDebugWire = nullptr;

	// Entity Id Value (Initialization UnKnown)
	Id m_entityId{ Id::UnKnown };
};

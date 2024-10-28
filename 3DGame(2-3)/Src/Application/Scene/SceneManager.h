#pragma once

class BaseScene;

class SceneManager
{
public :

	// シーン情報
	enum class SceneType
	{
		Debug,
		Title,
		Game,
	};

	enum Mode : uint32_t
	{
		Normal	   = Def::BitMaskPos0,
		Tuna	   = Def::BitMaskPos1,
		HardCore   = Def::BitMaskPos2,

		TimeLimit  = Def::BitMaskPos3,
		TimeAttack = Def::BitMaskPos4,
		
		Fish1      = Def::BitMaskPos5,
		Chicken    = Def::BitMaskPos6,
		Fish2      = Def::BitMaskPos7,
	};

	void PreUpdate();
	void Update(const float deltaTime);
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// 次のシーンをセット (次のフレームから切り替わる)
	void SetNextScene(SceneType nextScene)
	{
		m_nextSceneType = nextScene;
	}

	// 現在のシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();
	std::list<std::shared_ptr<KdGameObject>>&       WorkObjList();

	inline const auto CheckModeFilter(const Mode mode, const Mode filter) noexcept{ return (static_cast<uint32_t>(mode) & static_cast<uint32_t>(filter)) != Def::BitMaskPos0; }

	inline auto SetMode(const Mode mode) noexcept { m_mode = mode; }
	inline const auto GetMode() const noexcept { return m_mode; }

	// 現在のシーンにオブジェクトを追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj);

	// Add ObjctList Function (Emplace_Back)
	template <class T, typename... Args>
	inline auto AddObjList(Args&&... args) noexcept
	{
		static_assert(std::is_base_of<KdGameObject, T>::value, "T Must Be Derived From KdGameObject");
		WorkObjList().emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	// Add ObjctList And Create WeakPtr Function (Push_Back)
	template <class _T, typename... _Args>
	inline auto AddObjListAndWeak(std::weak_ptr<_T>& wpObj, _Args&&... args) noexcept
	{
		static_assert(std::is_base_of<KdGameObject, _T>::value, "_T Must Be Derived From KdGameObject");
		auto obj{ std::make_shared<_T>(std::forward<_Args>(args)...) };
		wpObj = obj;
		WorkObjList().push_back(obj);
	}

private :

	enum SoundType : size_t
	{
		Basic,
		VolumeUp,
		VolumeDown,
		VolumeMute,
		TypeMax
	};

	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init();

	// シーン切り替え関数
	void ChangeScene(SceneType sceneType);

	// サウンドボリューム制御関数
	void SoundUpdate() noexcept;

	// サウンドボリューム描画関数
	void SoundSpriteDraw() noexcept;

	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Title;
	
	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

	// サウンドテクスチャー
	std::shared_ptr<KdTexture> m_spSoundTex = nullptr;

	// サウンドテクスチャー切り取り用変数
	Math::Rectangle m_soundTexRect = {};

	// サウンドテクスチャー座標用変数
	Math::Vector2 m_soundTexPos = {};

	// すべてのサウンドのボリューム
	float m_masterVolume = static_cast<float>(NULL);

	// サウンドボリューム変動値
	float m_changeVol = static_cast<float>(NULL);

	// ミュートフラグ
	bool m_muteFlg = false;

	// キーフラグ
	bool m_volUpKeyFlg = false;
	bool m_volDownKeyFlg = false;
	bool m_volMuteKeyFlg = false;

	Mode m_mode{ Mode::Normal };
private:

	SceneManager() { Init(); }
	~SceneManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};

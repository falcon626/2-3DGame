#pragma once

// FMOD のカスタムデリータを定義
struct FMODSystemDeleter {
	void operator()(FMOD::System* system) const {
		if (system) {
			system->release();
		}
	}
};

struct FMODSoundDeleter {
	void operator()(FMOD::Sound* sound) const {
		if (sound) {
			sound->release();
		}
	}
};

class FlAudioManager {
public:
	FlAudioManager() { Init(); }
	~FlAudioManager() = default;

	// サウンドを読み込む関数
	std::shared_ptr<FMOD::Sound> LoadSound(const std::string& filePath);

	// サウンドを再生する関数
	void Play(const std::string& filePath);

	// 初期化関数
	void Init();

	// FMOD システムの更新関数
	void Update();

	FlAudioManager(const FlAudioManager&) = delete;
	FlAudioManager& operator=(const FlAudioManager&) = delete;
private:

	// FMOD::System を unique_ptr で管理
	std::unique_ptr<FMOD::System, FMODSystemDeleter> m_upSystem;
	// サウンドキャッシュ: ファイルパスをキーにした shared_ptr
	std::unordered_map<std::string, std::shared_ptr<FMOD::Sound>> m_soundCache;

	std::vector<std::shared_ptr<FMOD::Channel>> m_channels;
};
#pragma once

class FlAudioManager {
public:
	FlAudioManager() { Init(); }
	~FlAudioManager() = default;

	// サウンドを読み込む関数
	const std::shared_ptr<FMOD::Sound> LoadSound(const std::string& filePath);

	// サウンドを再生する関数
	void Play();
	void Play(const std::string& filePath, const bool isLoop = false);
	const bool IsPlay(const std::string& filePath);

	void Stop();
	void Stop(const std::string& filePath);

	void Set3DSoundSettings(const FMOD_VECTOR& position, const FMOD_VECTOR& velocity);
	void Set3DSoundSettings(const std::string& filePath, const FMOD_VECTOR& position, const FMOD_VECTOR& velocity);

	void SetVolume(float volume);
	void SetVolume(const std::string& filePath, float volume);

	void SetPitch(float pitch);
	void SetPitch(const std::string& filePath, float pitch);

	void Pause();
	void Pause(const std::string& filePath);

	void Resume();
	void Resume(const std::string& filePath);

	void SetReverb(float reverbLevel);
	void SetReverb(const std::string& filePath, float reverbLevel);

	// 初期化関数
	void Init();

	// FMOD システムの更新関数
	void Update();

	FlAudioManager(const FlAudioManager&) = delete;
	FlAudioManager& operator=(const FlAudioManager&) = delete;
private:

	// FMOD のカスタムデリータを定義
	struct FMODSystemDeleter {
		void operator()(FMOD::System* system) const {
			if (system) system->release();
		}
	};

	struct FMODSoundDeleter {
		void operator()(FMOD::Sound* sound) const {
			if (sound) sound->release();
		}
	};

	struct FMODChannelDeleter {
		void operator()(FMOD::Channel* channel) const {
			if (channel) channel->stop();
		}
	};

	// FMOD::System を unique_ptr で管理
	std::unique_ptr<FMOD::System, FMODSystemDeleter> m_upSystem;

	std::unordered_map<std::string, std::pair<std::shared_ptr<FMOD::Sound>, std::unique_ptr<FMOD::Channel, FMODChannelDeleter>>> m_soundController;
};
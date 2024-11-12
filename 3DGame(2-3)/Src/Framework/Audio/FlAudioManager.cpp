#include "FlAudioManager.h"

std::shared_ptr<FMOD::Sound> FlAudioManager::LoadSound(const std::string& filePath)
{
	// サウンドが既にキャッシュに存在する場合は、それを返す
	if (m_soundCache.find(filePath) != m_soundCache.end()) {
		return m_soundCache[filePath];
	}

	// サウンドが未ロードの場合、新しくロードする
	std::unique_ptr<FMOD::Sound, FMODSoundDeleter> newSound;
	FMOD::Sound* rawSound = nullptr;
	FMOD_RESULT result = m_upSystem->createSound(filePath.c_str(), FMOD_DEFAULT, nullptr, &rawSound);
	if (result != FMOD_OK) {
		throw std::runtime_error("Failed to load sound: " + filePath);
	}

	// 生ポインタを unique_ptr に変換
	newSound.reset(rawSound);

	// サウンドを shared_ptr に変換してキャッシュに格納
	std::shared_ptr<FMOD::Sound> spSound(newSound.release(), FMODSoundDeleter());
	m_soundCache[filePath] = spSound;
	return spSound;
}

void FlAudioManager::Play(const std::string& filePath)
{
	std::shared_ptr<FMOD::Sound> sound = LoadSound(filePath);
	FMOD::Channel* channel = nullptr;
	m_upSystem->playSound(sound.get(), nullptr, false, &channel);
}

void FlAudioManager::Init()
{
	FMOD::System* rawSystem = nullptr;
	FMOD::System_Create(&rawSystem);
	m_upSystem.reset(rawSystem); // unique_ptr に設定
	m_upSystem->init(512, FMOD_INIT_NORMAL, nullptr);
}

void FlAudioManager::Update()
{
	m_upSystem->update();
}

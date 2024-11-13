#include "FlAudioManager.h"

const std::shared_ptr<FMOD::Sound> FlAudioManager::LoadSound(const std::string& filePath)
{
	// サウンドが既にキャッシュに存在する場合は、それを返す
	if (m_soundController.find(filePath) != m_soundController.end()) return m_soundController[filePath].first;

	// サウンドが未ロードの場合、新しくロードする
	auto rawSound{ static_cast<FMOD::Sound*>(nullptr) };
	if (m_upSystem->createSound(filePath.c_str(), FMOD_DEFAULT, nullptr, &rawSound) != FMOD_OK)
	{
		_ASSERT_EXPR(false, "Failed To Create Sound");
		return nullptr;
	}

	// カスタムデリータを使った unique_ptr を作成
	auto upNewSound{ std::unique_ptr<FMOD::Sound, FMODSoundDeleter>(rawSound) };

	// shared_ptr に変換してキャッシュに格納
	auto spSound{ std::shared_ptr<FMOD::Sound>(upNewSound.release(), FMODSoundDeleter()) };
	m_soundController[filePath] = { spSound, nullptr }; 

	return spSound;
}

void FlAudioManager::Play()
{
	auto it{ m_soundController.begin() };

	while (it != m_soundController.end())
	{
		// サウンドをロードし、存在を保証
		if (!LoadSound(it->first)) return;

		// m_soundController からサウンドとチャンネルを取得
		auto& soundChannelPair{ m_soundController[it->first] };
		auto& spSound         { soundChannelPair.first };
		auto& upChannel       { soundChannelPair.second };

		auto mode{ FMOD_MODE{} };
		upChannel->getMode(&mode);

		if (spSound)
		{
			auto rawChannel{ static_cast<FMOD::Channel*>(nullptr) };
			m_upSystem->playSound(spSound.get(), nullptr, false, &rawChannel);

			if (rawChannel) rawChannel->setMode(mode);

			upChannel.reset(rawChannel);
		}

		++it;
	}
}

void FlAudioManager::Play(const std::string& filePath, const bool isLoop)
{
	// サウンドをロードし、存在を保証
	if (!LoadSound(filePath)) return;

	// m_soundController からサウンドとチャンネルを取得
	auto& soundChannelPair{ m_soundController[filePath] };
	auto& spSound         { soundChannelPair.first };
	auto& upChannel       { soundChannelPair.second };

	if (spSound)
	{
		auto rawChannel{ static_cast<FMOD::Channel*>(nullptr) };
		m_upSystem->playSound(spSound.get(), nullptr, false, &rawChannel);

		if (rawChannel && isLoop) rawChannel->setMode(FMOD_LOOP_NORMAL);

		upChannel.reset(rawChannel);
	}
}

const bool FlAudioManager::IsPlay(const std::string& filePath)
{
	auto it{ m_soundController.find(filePath) };
	auto is{ false };
	if (it != m_soundController.end() && it->second.second) it->second.second->isPlaying(&is);
	return is;
}

void FlAudioManager::Stop()
{
	auto it{ m_soundController.begin() };
	while (it != m_soundController.end())
	{
		if (it->second.second) (*it).second.second->stop();
		++it;
	}
}

void FlAudioManager::Stop(const std::string& filePath)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) it->second.second->stop();
}

void FlAudioManager::Set3DSoundSettings(const FMOD_VECTOR& position, const FMOD_VECTOR& velocity)
{
	auto it{ m_soundController.begin() };
	while (it != m_soundController.end())
	{
		if (it->second.second) (*it).second.second->set3DAttributes(&position, &velocity);
		++it;
	}
}

void FlAudioManager::Set3DSoundSettings(const std::string& filePath, const FMOD_VECTOR& position, const FMOD_VECTOR& velocity)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) it->second.second->set3DAttributes(&position, &velocity);
}

void FlAudioManager::SetVolume(float volume)
{
	auto it{ m_soundController.begin() };
	while (it != m_soundController.end())
	{
		if (it->second.second) (*it).second.second->setVolume(volume);
		++it;
	}
}

void FlAudioManager::SetVolume(const std::string& filePath, float volume)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) it->second.second->setVolume(volume);
}

void FlAudioManager::SetPitch(float pitch)
{
	auto it{ m_soundController.begin() };
	while (it != m_soundController.end())
	{
		if (it->second.second) (*it).second.second->setPitch(pitch);
		++it;
	}
}

void FlAudioManager::SetPitch(const std::string& filePath, float pitch)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) it->second.second->setPitch(pitch);
}

void FlAudioManager::Pause()
{
	auto it{ m_soundController.begin() };
	while (it != m_soundController.end())
	{
		if (it->second.second) (*it).second.second->setPaused(true);
		++it;
	}
}

void FlAudioManager::Pause(const std::string& filePath)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) it->second.second->setPaused(true);
}

void FlAudioManager::Resume()
{
	auto it{ m_soundController.begin() };
	while (it != m_soundController.end())
	{
		if (it->second.second) (*it).second.second->setPaused(false);
		++it;
	}
}

void FlAudioManager::Resume(const std::string& filePath)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) it->second.second->setPaused(false);
}

void FlAudioManager::SetReverb(float reverbLevel)
{
	auto it{ m_soundController.begin() };
	auto rawReverbDSP{ static_cast<FMOD::DSP*>(nullptr) };

	m_upSystem->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &rawReverbDSP);
	rawReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_WETLEVEL, reverbLevel);

	while (it != m_soundController.end())
	{
		if(it->second.second) (*it).second.second->addDSP(0, rawReverbDSP);
		++it;
	}
	rawReverbDSP->release();
}

void FlAudioManager::SetReverb(const std::string& filePath, float reverbLevel)
{
	auto it{ m_soundController.find(filePath) };
	if (it != m_soundController.end() && it->second.second) 
	{
		auto rawReverbDSP{ static_cast<FMOD::DSP*>(nullptr) };
		m_upSystem->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &rawReverbDSP);
		rawReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_WETLEVEL, reverbLevel);
		it->second.second->addDSP(0, rawReverbDSP);
		rawReverbDSP->release();
	}
}

void FlAudioManager::Init()
{
	auto rawSystem{ static_cast<FMOD::System*>(nullptr) };

	FMOD::System_Create(&rawSystem);
	m_upSystem.reset(rawSystem);
	m_upSystem->init(512, FMOD_INIT_NORMAL, nullptr);
}

void FlAudioManager::Update()
{
	m_upSystem->update();
}

#pragma once

#include "Audio/FlAudioManager.h"
#include "Binary/FlBinaryManager.hpp"
#include "Json/FlJsonDataManager.hpp"

class FlResourceAdministrator
{
public:

	void PreLoader(const std::initializer_list<std::string>& paths);
	void AllClear() noexcept;

	inline const auto& GetAudioInstance()  const noexcept { return m_spAudio; }
	inline const auto& GetBinaryInstance() const noexcept { return m_spBinary; }
	inline const auto& GetJsonInstance()   const noexcept { return m_spJson; }

	static auto& Instance() noexcept
	{
		static auto instance{ FlResourceAdministrator{} };
		return instance;
	}
private:

	FlResourceAdministrator() noexcept;
	~FlResourceAdministrator() = default;

	FlResourceAdministrator(const FlResourceAdministrator&) = delete;
	FlResourceAdministrator& operator=(const FlResourceAdministrator&) = delete;

	std::shared_ptr<FlAudioManager>    m_spAudio;
	std::shared_ptr<FlBinaryManager>   m_spBinary;
	std::shared_ptr<FlJsonDataManager> m_spJson;
};
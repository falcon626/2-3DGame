﻿#include "FlResourceAdministrator.h"

FlResourceAdministrator::FlResourceAdministrator() noexcept
	: m_spAudio { std::make_shared<FlAudioManager>() }
	, m_spBinary{ std::make_shared<FlBinaryManager>() }
	, m_spJson  { std::make_shared<FlJsonDataManager>() }
{}

void FlResourceAdministrator::PreLoader(const std::initializer_list<std::string>& paths)
{
	for (decltype(auto) path : paths)
	{
		const auto exte{ Str::FileExtensionSearcher(path) };

		if (exte == "wav" || exte == "mp3")
		{
			m_spAudio->LoadSound(path);
			continue;
		}
		else if (exte == "gltf" || exte == "png")
		{
			
		}
	}
}

void FlResourceAdministrator::AllClear() noexcept
{
	m_spBinary->ClearCache();
}

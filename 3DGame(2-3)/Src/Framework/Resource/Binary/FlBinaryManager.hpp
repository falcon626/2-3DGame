#pragma once

#include "FlBinaryAccessor.hpp"

class FlBinaryManager
{
public:
	FlBinaryManager()  = default;
	~FlBinaryManager() = default;

	template <typename T>
	const std::shared_ptr<std::vector<T>> LoadData(const std::string& filename) 
	{
		auto it{ m_dataCache.find(filename) };
		if (it != m_dataCache.end()) return std::static_pointer_cast<std::vector<T>>(it->second);

		auto newData{ std::make_shared<std::vector<T>>() };
		auto elementsNum{ Def::UIntZero };

		if (m_accessor.Load(filename, *newData, elementsNum)) 
		{
			m_dataCache[filename] = newData;
			return newData;
		}
		return nullptr;
	}

	template <typename T>
	bool SaveData(const std::string& filename, const std::vector<T>& data) 
	{
		if (m_accessor.Save(filename, data)) 
		{
			m_dataCache[filename] = std::make_shared<std::vector<T>>(data);
			return true;
		}
		return false;
	}

	inline auto ClearCache() noexcept { m_dataCache.clear(); }

private:
	FlBinaryManager(const FlBinaryManager&) = delete;
	FlBinaryManager& operator=(const FlBinaryManager&) = delete;

	FlBinaryAccessor m_accessor;
	std::unordered_map<std::string, std::shared_ptr<void>> m_dataCache;
};

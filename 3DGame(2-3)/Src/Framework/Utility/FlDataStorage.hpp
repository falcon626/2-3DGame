#pragma once

// <Flyweight>
class FlDataStorage
{
public:
	// Common Path For All Omitted Models
	const auto GetModelData(const std::string& path) noexcept { return GetData(m_modelStorage, ModelPath + path); }

	// Common Path For All Omitted Textures
	const auto GetTexture(const std::string& path)   noexcept { return GetData(m_textureStorage, TexturePath + path); }

	// Cache Of KdModelDates
	auto PreLoadModelsData(const std::initializer_list<std::string>& paths) noexcept { PreLoadData(m_modelStorage, paths, ModelPath); }

	// Cache Of KdTextures
	auto PreLoadTextures(const std::initializer_list<std::string>& paths)   noexcept { PreLoadData(m_textureStorage, paths, TexturePath); }

	// Common Path For All Omitted
	template<class DataType>
	const auto GetData(const std::string& path) noexcept
	{
		const auto Extension{ Str::FileExtensionSearcher(path) };

		if      (Extension == ModelExtension)   return GetData(m_modelStorage, ModelPath + path);
		else if (Extension == TextureExtension) return GetData(m_textureStorage, TexturePath + path);
		else return nullptr;
	}

	// Cache Of Data
	auto PreLoadData(const std::initializer_list<std::string>& paths) noexcept
	{
		for (decltype(auto) path : paths)
		{
			const auto Extension{ Str::FileExtensionSearcher(path) };

			if      (Extension == ModelExtension)   LoadData(m_modelStorage,   ModelPath + path);
			else if (Extension == TextureExtension) LoadData(m_textureStorage, TexturePath + path);
			else { _ASSERT_EXPR(false, L"This Path Is Not Model And Texture"); continue; }
		}
	}

	// Dump Not Used Resource
	auto ReleaseUnusedResources() noexcept
	{
		ClearUnusedData(m_modelStorage);
		ClearUnusedData(m_textureStorage);
	}

	// Compulsion Dump All Resource
	auto ClearAllResources() noexcept
	{
		m_modelStorage.clear();
		m_textureStorage.clear();
	}

	// Only Instance
	static auto& Instance() noexcept
	{
		static FlDataStorage instance;
		return instance;
	}

private:
	FlDataStorage () noexcept = default;
	~FlDataStorage() noexcept { ClearAllResources(); }

	template<class DataType>
	std::shared_ptr<DataType> LoadData(std::unordered_map<std::string, std::shared_ptr<DataType>>& storage, const std::string& fileName) const noexcept
	{
		const auto NewData{ std::make_shared<DataType>() };
		if (!NewData->Load(fileName))
		{
			assert(NULL && L"FlDataStorage::LoadData: Not Found File; Please Check File Path");
			return nullptr;
		}
		storage[fileName] = NewData;
		return NewData;
	}

	template<class DataType>
	std::shared_ptr<DataType> GetData(std::unordered_map<std::string, std::shared_ptr<DataType>>& storage, const std::string& fullPath) noexcept
	{
		auto it{ storage.find(fullPath) };
		if (it != storage.end())
			return it->second;

		return LoadData(storage, fullPath);
	}

	template<class DataType>
	auto PreLoadData(std::unordered_map<std::string, std::shared_ptr<DataType>>& storage, const std::vector<std::string>& paths, const std::string& basePath) noexcept
	{
		for (decltype(auto) path : paths)
			LoadData(storage, basePath + path);
	}

	template<class DataType>
	auto ClearUnusedData(std::unordered_map<std::string, std::shared_ptr<DataType>>& storage) noexcept
	{
		for (auto it{ storage.begin() }; it != storage.end();)
		{
			if (it->second.use_count() == Def::LongOne) it = storage.erase(it);
			else ++it;
		}
	}

	std::unordered_map<std::string, std::shared_ptr<KdModelData>> m_modelStorage;
	std::unordered_map<std::string, std::shared_ptr<KdTexture>>   m_textureStorage;

	const std::string ModelPath  { "Asset/Models/" };
	const std::string TexturePath{ "Asset/Textures/" };

	const std::string ModelExtension  { "gltf" };
	const std::string TextureExtension{ "png" };
};
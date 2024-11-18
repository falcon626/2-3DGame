#pragma once

class FlBinaryAccessor // If The File Is Not Open Return False
{
public:

	FlBinaryAccessor()  = default;
	~FlBinaryAccessor() = default;

	FlBinaryAccessor(const FlBinaryAccessor&) = delete;
	FlBinaryAccessor& operator=(const FlBinaryAccessor&) = delete;

	template <typename T>
	auto Save(const std::string& filename, const std::vector<T>& save) noexcept
	{
		auto file{ std::ofstream{filename, std::ios::binary} };
		if (file.is_open())
		{
			// Save Data
			file.write(reinterpret_cast<const char*>(save.data()), save.size() * sizeof(T));
			file.close();
			return true;
		}
		else return false;
	}

	template <typename _T>
	auto Load(const std::string filename, std::vector<_T>& load, size_t& elementsNum) noexcept
	{
		auto file{ std::ifstream{filename, std::ios::binary} };
		if (file.is_open()) 
		{
			// Get File Size
			file.seekg(NULL, std::ios::end);
			auto size{ std::streamsize{file.tellg()} };
			file.seekg(NULL, std::ios::beg);

			// File Size Check
			if (size % sizeof(_T) != NULL) return false;

			// Load Data Element Count
			elementsNum = static_cast<size_t>(size) / sizeof(_T);

			// Load Data
			load.resize(elementsNum);
			if (file.read(reinterpret_cast<char*>(load.data()), size))
			{
				file.close();
				return true;
			}
			else
			{
				file.close();
				return false;
			}
		}
		else return false;
	}

private:

};
#pragma once

class FlJsonDataManager {
public:
	const auto FromJson(const std::string_view& json) noexcept {
		if (m_document.Parse(json.data()).HasParseError()) 
		{
			_ASSERT_EXPR(false, "JSON Parse Error");
			return false;
		}
		return true;
	}

	const std::string ToJson() const noexcept {
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		m_document.Accept(writer);
		return buffer.GetString();
	}

	template <typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
	const auto GetValue(const std::string_view& memberName) noexcept {
		if constexpr (std::is_same_v<U, uint32_t>) {
			return m_document[memberName.data()].GetUint();
		}
		else if constexpr (std::is_same_v<U, uint64_t>) {
			return m_document[memberName.data()].GetUint64();
		}
		else if constexpr (std::is_same_v<U, int32_t>) {
			return m_document[memberName.data()].GetInt();
		}
		else if constexpr (std::is_same_v<U, int64_t>) {
			return m_document[memberName.data()].GetInt64();
		}
	}

	template <typename U, typename = std::enable_if_t<std::is_floating_point_v<U>>>
	auto GetValue(const std::string_view& memberName) const noexcept -> const U {
		return m_document[memberName.data()].GetDouble();
	}

	template <typename U, typename = std::enable_if_t<std::is_same_v<U, bool>>>
	auto GetValue(const std::string_view& memberName) const noexcept -> const U {
		return m_document[memberName.data()].GetBool();
	}

	template <typename U, typename = std::enable_if_t<std::is_same_v<U, std::string>>>
	auto GetValue(const std::string_view& memberName) const noexcept -> const U {
		return m_document[memberName.data()].GetString();
	}

	template <typename U, typename = std::enable_if_t<std::is_array_v<U>>>
	auto GetValue(const std::string_view& memberName) const noexcept -> const U {
		using ElementType = std::remove_extent_t<U>;

		const auto& arr = m_document[memberName.data()];

		std::vector<ElementType> result;

		if (arr.IsArray()) {
			for (auto itr = arr.Begin(); itr != arr.End(); ++itr) {
				if constexpr (std::is_same_v<ElementType, std::string>) {
					result.push_back(itr->GetString());
				}
				else if constexpr (std::is_floating_point_v<ElementType>) {
					result.push_back(static_cast<ElementType>(itr->GetDouble()));
				}
				else if constexpr (std::is_integral_v<ElementType>) {
					result.push_back(static_cast<ElementType>(itr->GetInt()));
				}
			}
		}

		return result;
	}

	template <typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
	auto SetValue(const std::string_view& memberName, const U&& value) noexcept {
		if constexpr (std::is_same_v<U, uint32_t>) {
			m_document[memberName.data()].SetUint(std::forward<U>(value));
		}
		else if constexpr (std::is_same_v<U, uint64_t>) {
			m_document[memberName.data()].SetUint64(std::forward<U>(value));
		}
		else if constexpr (std::is_same_v<U, int32_t>) {
			m_document[memberName.data()].SetInt(std::forward<U>(value));
		}
		else if constexpr (std::is_same_v<U, int64_t>) {
			m_document[memberName.data()].SetInt64(std::forward<U>(value).c_str(), m_document.GetAllocator());
		}
	}

	template <typename U, typename = std::enable_if_t<std::is_floating_point_v<U>>>
	auto SetValue(const std::string_view& memberName, const U&& value) noexcept {
		m_document[memberName.data()].SetDouble(std::forward<U>(value));
	}

	template <typename U, typename = std::enable_if_t<std::is_same_v<U, bool>>>
	auto SetValue(const std::string_view& memberName, const U&& value) noexcept {
		m_document[memberName.data()].SetBool(std::forward<U>(value));
	}

	template <typename U, typename = std::enable_if_t<std::is_same_v<U, std::string>>>
	auto SetValue(const std::string_view& memberName, const U&& value) noexcept {
		m_document[memberName.data()].SetString(std::forward<U>(value).c_str(), m_document.GetAllocator());
	}

	template <typename U, typename = std::enable_if_t<std::is_array_v<U>>>
	auto SetValue(const std::string_view& memberName, const U&& values) noexcept {
		using ElementType = std::remove_extent_t<U>;

		auto& arr = m_document[memberName.data()];
		arr.SetArray();

		for (const auto& value : values) {
			rapidjson::Value elementValue;
			if constexpr (std::is_same_v<ElementType, std::string>) {
				elementValue.SetString(value.c_str(), m_document.GetAllocator());
			}
			else if constexpr (std::is_floating_point_v<ElementType>) {
				elementValue.SetDouble(value);
			}
			else if constexpr (std::is_integral_v<ElementType>) {
				elementValue.SetInt(value);
			}
			arr.PushBack(elementValue, m_document.GetAllocator());
		}
	}

private:
	rapidjson::Document m_document;
};
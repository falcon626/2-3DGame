class FlJsonDataManager {
public:

	FlJsonDataManager()  = default;
	~FlJsonDataManager() = default;

	FlJsonDataManager(const FlJsonDataManager&) = delete;
	FlJsonDataManager& operator=(const FlJsonDataManager&) = delete;

	const auto FromJson(const std::string_view& json) noexcept {
		if (m_document.Parse(json.data()).HasParseError()) {
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

	// 統一されたゲッター関数
	template <typename T>
	auto GetValue(const std::string_view& memberName) const noexcept {
		static_assert(
			std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, bool> || std::is_same_v<T, std::string> || std::is_array_v<T>,
			"Invalid Type for GetValue"
			);

		if constexpr (std::is_integral_v<T>) {
			if constexpr (std::is_same_v<T, uint32_t>) {
				return m_document[memberName.data()].GetUint();
			}
			else if constexpr (std::is_same_v<T, uint64_t>) {
				return m_document[memberName.data()].GetUint64();
			}
			else if constexpr (std::is_same_v<T, int32_t>) {
				return m_document[memberName.data()].GetInt();
			}
			else if constexpr (std::is_same_v<T, int64_t>) {
				return m_document[memberName.data()].GetInt64();
			}
		}
		else if constexpr (std::is_floating_point_v<T>) {
			return static_cast<T>(m_document[memberName.data()].GetDouble());
		}
		else if constexpr (std::is_same_v<T, bool>) {
			return m_document[memberName.data()].GetBool();
		}
		else if constexpr (std::is_same_v<T, std::string>) {
			return std::string(m_document[memberName.data()].GetString());
		}
		else if constexpr (std::is_array_v<T>) {
			using ElementType = std::remove_extent_t<T>;
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
	}

	// 統一されたセッター関数
	template <typename T>
	auto SetValue(const std::string_view& memberName, const T& value) noexcept {
		static_assert(
			std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, bool> || std::is_same_v<T, std::string> || std::is_array_v<T>,
			"Invalid Type for SetValue"
			);

		if constexpr (std::is_integral_v<T>) {
			if constexpr (std::is_same_v<T, uint32_t>) {
				m_document[memberName.data()].SetUint(value);
			}
			else if constexpr (std::is_same_v<T, uint64_t>) {
				m_document[memberName.data()].SetUint64(value);
			}
			else if constexpr (std::is_same_v<T, int32_t>) {
				m_document[memberName.data()].SetInt(value);
			}
			else if constexpr (std::is_same_v<T, int64_t>) {
				m_document[memberName.data()].SetInt64(value);
			}
		}
		else if constexpr (std::is_floating_point_v<T>) {
			m_document[memberName.data()].SetDouble(value);
		}
		else if constexpr (std::is_same_v<T, bool>) {
			m_document[memberName.data()].SetBool(value);
		}
		else if constexpr (std::is_same_v<T, std::string>) {
			m_document[memberName.data()].SetString(value.c_str(), m_document.GetAllocator());
		}
		else if constexpr (std::is_array_v<T>) {
			using ElementType = std::remove_extent_t<T>;

			auto& arr = m_document[memberName.data()];
			arr.SetArray();

			for (const auto& val : value) {
				rapidjson::Value elementValue;
				if constexpr (std::is_same_v<ElementType, std::string>) {
					elementValue.SetString(val.c_str(), m_document.GetAllocator());
				}
				else if constexpr (std::is_floating_point_v<ElementType>) {
					elementValue.SetDouble(val);
				}
				else if constexpr (std::is_integral_v<ElementType>) {
					elementValue.SetInt(val);
				}
				arr.PushBack(elementValue, m_document.GetAllocator());
			}
		}
	}

private:

	rapidjson::Document m_document;
};
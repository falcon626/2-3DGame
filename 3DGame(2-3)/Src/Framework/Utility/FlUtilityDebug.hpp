#pragma once

class DebugLogger
{
public:
	DebugLogger(const std::string& filename = "Asset/Data/Log/DebugLog.txt")
	{
		m_logFile.open(filename, std::ios::out | std::ios::app);
		if (!m_logFile) _ASSERT_EXPR(false, L"ログファイルがありません");
	}

	~DebugLogger()
	{
		if (m_logFile.is_open()) m_logFile.close();
	}

	void LogDebug(const std::string& message, const char* file, int line)
	{
		if (m_logFile.is_open())
		{
			m_logFile << GetCurrentDateTime() << std::endl
				<< "[File: " << file << "] "
				<< "[Line: " << line << "] "
				<< message << std::endl;
		}
	}

private:
	std::ofstream m_logFile;

	std::string GetCurrentDateTime()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		auto duration = now.time_since_epoch();

		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration - seconds);

		std::tm localTime;
#ifdef _WIN32
		localtime_s(&localTime, &now_time_t);
#else
		localtime_r(&now_time_t, &localTime);
#endif
		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "."
			<< std::setfill('0') << std::setw(9) << nanoseconds.count();
		return oss.str();
	}
};

#if _DEBUG
	#define DEBUG_LOG(logger, message) logger->LogDebug(message, __FILE__, __LINE__)
#else
	#define DEBUG_LOG(logger, message) ((void)NULL)
#endif // _DEBUG
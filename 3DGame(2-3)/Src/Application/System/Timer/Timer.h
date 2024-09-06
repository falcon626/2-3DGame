#pragma once

class Timer
{
public:
    Timer () noexcept : m_isRunning(false) {}
	~Timer() noexcept = default;

    void Start() noexcept;

    void Stop() noexcept;

    void Restart() noexcept;

    void Resume() noexcept;

	void Reset() noexcept;

    uint32_t const ElapsedSeconds() const noexcept;

private:
    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::steady_clock::time_point m_stopTime;
    bool m_isRunning;
};

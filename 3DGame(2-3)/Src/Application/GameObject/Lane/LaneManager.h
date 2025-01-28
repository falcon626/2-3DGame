#pragma once

class BaseLaneObj;
class LaneObject;
class Player;

class LaneManager
{
public:
	explicit LaneManager(const uint32_t nearNum, const uint32_t tileNum, const uint32_t randMax, const float startPosX, const float initializeLanePosZ) noexcept;
	~LaneManager() = default;

	void PreUpdate(const float playerZ);
	void Update();
	void AddLane();

	const std::list<std::shared_ptr<KdGameObject>> GetTilesList(const float playerZ) const;

	inline const auto& GetLaneData()     const noexcept { return m_laneData; }
	inline const auto& GetLastLaneData() const noexcept { return m_wpLastLane; }

	void KillLane(const uint32_t element) noexcept;

	void AddWeakPtr(const std::weak_ptr<LaneObject> newElement) noexcept;

	enum class LaneNumber : uint32_t
	{
		Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
		Ten, Eleven, Twelve, Thirteen, Fourteen, Fifteen, Sixteen, Seventeen, Eighteen, Nineteen,
		Twenty, TwentyOne, TwentyTwo, TwentyThree, TwentyFour,
		Max,
	};
private:
	std::array<std::weak_ptr<LaneObject>, static_cast<uint32_t>(LaneNumber::Max)> m_laneData;

	std::weak_ptr<LaneObject> m_wpLastLane;
	
	const uint32_t NearLaneNum;
	const uint32_t TileNum;
	const uint32_t RandMax;

	const float OffsetStartPosX;


	uint32_t m_currentIndex;
	float    m_laneZ;
};
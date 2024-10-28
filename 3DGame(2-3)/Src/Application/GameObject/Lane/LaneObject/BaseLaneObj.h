#pragma once

class CommonTile;

class BaseLaneObj : public KdGameObject
{
public:
	BaseLaneObj () = default;
	virtual ~BaseLaneObj() override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit()                   override;

	void PreUpdate()override;

	virtual inline const bool IsUp() const noexcept { return m_isUp; }

	inline const auto GetTilesList() const noexcept { return m_tilesList; }

protected:

	// Add ObjctList Function (Emplace_Back)
	template <class T, typename... Args>
	inline auto AddObjList(Args&&... args) noexcept
	{
		static_assert(std::is_base_of<CommonTile, T>::value, "T Must Be Derived From CommonTile");
		m_tilesList.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	std::list<std::shared_ptr<KdGameObject>> m_tilesList;

	bool m_isUp{ false };
private:

	//uint32_t m_tilesNum;
	//float    m_tilesStartPosX;
};
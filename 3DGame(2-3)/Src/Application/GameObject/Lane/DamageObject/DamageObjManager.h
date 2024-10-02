#pragma once

class DamageObjManager
{
public:
	DamageObjManager()  = default;
	~DamageObjManager() = default;

	void AddDamaObj();

	inline const auto& GetDamaList() const noexcept { return m_damaObjList; }
private:
	std::list<std::shared_ptr<KdGameObject>> m_damaObjList;
};
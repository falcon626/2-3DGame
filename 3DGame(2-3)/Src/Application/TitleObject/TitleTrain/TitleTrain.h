#pragma once
#include "../../ExtensionBaseObject/BaseBasic3DObject/BaseBasic3DObject.hpp"

class CommonTile;

class TitleTrain : public  KdGameObject
{
public:
	TitleTrain();
	~TitleTrain() override = default;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;
private:
	class TerainTag {};

	class Tile : public BaseBasic3DObject, TerainTag
	{
	public:
		explicit Tile(const std::string_view& path, const Math::Vector3& pos) noexcept;
		~Tile() override = default;

		void Update() override;

		inline const auto GetPath() const noexcept { return m_path; }
	private:
		Math::Vector3 m_pos;
		std::string m_path;
	};

	// Add ObjctList Function (Emplace_Back)
	template <class T, typename... Args>
	inline auto AddObjList(Args&&... args) noexcept
	{
		static_assert(std::is_base_of<TerainTag, T>::value, "T Must Be Derived From TerainTag");
		m_terainList.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	std::list<std::shared_ptr<Tile>> m_terainList;
};
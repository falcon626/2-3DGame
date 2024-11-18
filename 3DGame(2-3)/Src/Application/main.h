#pragma once

struct ImGuiAppLog
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
	bool                AutoScroll;
	bool                ScrollToBottom;

	ImGuiAppLog()
	{
		AutoScroll = true;
		ScrollToBottom = false;
		Clear();
	}

	void    Clear()
	{
		Buf.clear();
		LineOffsets.clear();
		LineOffsets.push_back(0);
	}

	void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size + 1);
		if (AutoScroll)
			ScrollToBottom = true;
	}

	void OutputDebugStringAlpha(const std::string& debugStr)
	{
		OutputDebugStringA(debugStr.c_str());
	}

	void    Draw(const char* title, bool* p_open = NULL)
	{
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			if (ImGui::Checkbox("Auto-scroll", &AutoScroll))
				if (AutoScroll)
					ScrollToBottom = true;
			ImGui::EndPopup();
		}

		// Main window
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		bool clear = ImGui::Button("Clear");
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);

		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		if (clear)
			Clear();
		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();
		if (Filter.IsActive())
		{
			for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				if (Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (ScrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();
		ImGui::End();
	}
};

struct ImguiPosition
{
	std::unordered_map<std::string, Math::Vector3> m_positions;
	std::string									   m_currentId;

	auto Registration(const std::string& id, const Math::Vector3& pos) noexcept { m_positions[id] = pos; }

	auto Draw() noexcept
	{
		if (ImGui::Button("Select Object ID")) ImGui::OpenPopup("Select Object ID");

		if (ImGui::BeginPopup("Select Object ID"))
		{
			for (const auto& pair : m_positions)
				if (ImGui::Selectable(("Object ID: " + pair.first).c_str(), m_currentId == pair.first)) m_currentId = pair.first;
			ImGui::EndPopup();
		}

        if (m_positions.find(m_currentId) != m_positions.end())
        {
			auto& pos{ m_positions[m_currentId] };
			// Slider for X component
			float x = pos.x;
			if (ImGui::SliderFloat("X", &x, -100.0f, 100.0f))
				pos.x = x;
			ImGui::SameLine();
			if (ImGui::InputFloat("##XInput", &pos.x, 0.0f, 0.0f, "%.3f"))
				pos.x = std::clamp(pos.x, -FLT_MAX, FLT_MAX);

			// Slider for Y component
			float y = pos.y;
			if (ImGui::SliderFloat("Y", &y, -100.0f, 100.0f))
				pos.y = y;
			ImGui::SameLine();
			if (ImGui::InputFloat("##YInput", &pos.y, 0.0f, 0.0f, "%.3f"))
				pos.y = std::clamp(pos.y, -FLT_MAX, FLT_MAX);

			// Slider for Z component
			float z = pos.z;
			if (ImGui::SliderFloat("Z", &z, -100.0f, 100.0f))
				pos.z = z;
			ImGui::SameLine();
			if (ImGui::InputFloat("##ZInput", &pos.z, 0.0f, 0.0f, "%.3f"))
				pos.z = std::clamp(pos.z, -FLT_MAX, FLT_MAX);

			if (ImGui::Button("Save"))
			{
				for (const auto& pair : m_positions)
				{
					std::vector parameter{ pair.second.x,pair.second.y,pair.second.z };
					auto uniqueName{ pair.first };

					FlResourceAdministrator::Instance().GetBinaryInstance()->Save("Asset/Data/ObjectPositionParameter/" + uniqueName + ".dat", parameter);
				}
			}
        }
    }

	const auto& Here (const std::string& id) const noexcept { return m_positions.at(id); }
};

//============================================================
// アプリケーションクラス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// メンバ
public:

	// アプリケーション実行
	void Execute();

	// アプリケーション終了
	void End() { m_endFlag = true; }
	int GetNowFPS() const { return static_cast<int>(m_fpsController.GetFPS()); }

	// ImGui
	ImGuiAppLog m_log;

	ImguiPosition m_ImPos;

private:

	void KdBeginUpdate();
	void PreUpdate();
	void Update(const float deltaTime);
	void PostUpdate();
	void KdPostUpdate();

	void KdBeginDraw(bool usePostProcess = true);
	void PreDraw();
	void Draw();
	void PostDraw();
	void DrawSprite();
	void KdPostDraw();

	// アプリケーション初期化
	bool Init(int w, int h);

	// アプリケーション解放
	void Release();

	// ImGui初期化
	void ImGuiInit();

	// ImGui描画処理
	void ImGuiProcess();

	// ImGui解放
	void ImGuiRelease();

	// FPSコントローラー
	FlFPSController m_fpsController;

	// ゲーム終了フラグ trueで終了する
	bool			m_endFlag = false;

//=====================================================
// シングルトンパターン
//=====================================================
private:

	Application() {}

public:
	static Application &Instance(){
		static Application Instance;
		return Instance;
	}
};

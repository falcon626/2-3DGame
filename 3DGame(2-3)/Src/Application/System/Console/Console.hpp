#pragma once

class Console final {
private:
	//インスタンス
	static Console* Instance;

	FILE* fp{ nullptr };

public:
	//コピーコンストラクタ禁止
	Console(const Console&) = delete;
	Console(Console&&) = delete;

	//代入禁止
	Console& operator=(const Console&) = delete;
	Console& operator=(Console&&) = delete;
	Console& operator=(Console) = delete;

private:
	//コンストラクタ
	Console() {

		AllocConsole();						//コンソール作成

		//閉じるボタンを無効にする
		RemoveMenu(GetSystemMenu(GetConsoleWindow(), FALSE),
			SC_CLOSE, MF_BYCOMMAND);

		//ワイド文字にする
		setlocale(LC_ALL, "Japanese");

		//タイトル変更
		SetConsoleTitleW(L"デバッグ用コンソール");

		//背景強調　・　文字色を　緑　にする
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);

	}

	//デストラクタ
	~Console() {
		FreeConsole();						//コンソール削除
	}

	//現在時刻の取得
	std::string time_acquisition()const {

		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string now_time(20, '\0');

		tm imanojikan;
		localtime_s(&imanojikan, &now);
		std::strftime(&now_time[0], now_time.size(), "%Y-%m-%d %H:%M:%S", &imanojikan);

		return now_time;
	}

public:

	//インスタンスの作成
	static void Create() {
		if (!Instance) {
			Instance = new Console;
		}
	}

	//インスタンスの破棄
	static void destroy() {
		delete Instance;				//インスタンス解放　デストラクタが呼ばれる
		Instance = nullptr;
	}

	//コンソールインスタンスを渡す
	static Console* get_Instance() {
		return Instance;
	}

	////////////////////////////////////////////////////////////////////////////////

	//コンソールクリア
	void Clear()const {
		std::system("cls");//画面クリア
	}

	//Lineを引く
	void LINE(int num = 1) {

		freopen_s(&fp, "CONOUT$", "w", stdout);		//書込可能にする

		for (int i = 0; i < num; i++) {
			std::wcout << L"----------------------------------------------------------------------------------------------------------------------" << std::endl;
		}

		freopen_s(&fp, "/dev/null", "w", stdout);	//書込禁止にする
	}

	//書き込み
	template<typename T>
	void write(const T& out) {

		//nullptrだったら終了
		if (!Instance) {
			MessageBoxW(NULL, L"コンソールオブジェクトがありません", L"err", MB_ICONERROR | MB_OK);
			return;
		}

		freopen_s(&fp, "CONOUT$", "w", stdout);		//書込可能にする

		std::wcout << time_acquisition().c_str();

		std::wcout << L"| " << out << std::endl;

		freopen_s(&fp, "/dev/null", "w", stdout);	//書込禁止にする
	}

	//operatorで書込む
	template<typename T>
	void operator<<(const T& out) {
		write(out);
	}

};

Console* Console::Instance = nullptr;
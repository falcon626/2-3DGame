#pragma once

class Console final {
private:
	//�C���X�^���X
	static Console* Instance;

	FILE* fp{ nullptr };

public:
	//�R�s�[�R���X�g���N�^�֎~
	Console(const Console&) = delete;
	Console(Console&&) = delete;

	//����֎~
	Console& operator=(const Console&) = delete;
	Console& operator=(Console&&) = delete;
	Console& operator=(Console) = delete;

private:
	//�R���X�g���N�^
	Console() {

		AllocConsole();						//�R���\�[���쐬

		//����{�^���𖳌��ɂ���
		RemoveMenu(GetSystemMenu(GetConsoleWindow(), FALSE),
			SC_CLOSE, MF_BYCOMMAND);

		//���C�h�����ɂ���
		setlocale(LC_ALL, "Japanese");

		//�^�C�g���ύX
		SetConsoleTitleW(L"�f�o�b�O�p�R���\�[��");

		//�w�i�����@�E�@�����F���@�΁@�ɂ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);

	}

	//�f�X�g���N�^
	~Console() {
		FreeConsole();						//�R���\�[���폜
	}

	//���ݎ����̎擾
	std::string time_acquisition()const {

		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string now_time(20, '\0');

		tm imanojikan;
		localtime_s(&imanojikan, &now);
		std::strftime(&now_time[0], now_time.size(), "%Y-%m-%d %H:%M:%S", &imanojikan);

		return now_time;
	}

public:

	//�C���X�^���X�̍쐬
	static void Create() {
		if (!Instance) {
			Instance = new Console;
		}
	}

	//�C���X�^���X�̔j��
	static void destroy() {
		delete Instance;				//�C���X�^���X����@�f�X�g���N�^���Ă΂��
		Instance = nullptr;
	}

	//�R���\�[���C���X�^���X��n��
	static Console* get_Instance() {
		return Instance;
	}

	////////////////////////////////////////////////////////////////////////////////

	//�R���\�[���N���A
	void Clear()const {
		std::system("cls");//��ʃN���A
	}

	//Line������
	void LINE(int num = 1) {

		freopen_s(&fp, "CONOUT$", "w", stdout);		//�����\�ɂ���

		for (int i = 0; i < num; i++) {
			std::wcout << L"----------------------------------------------------------------------------------------------------------------------" << std::endl;
		}

		freopen_s(&fp, "/dev/null", "w", stdout);	//�����֎~�ɂ���
	}

	//��������
	template<typename T>
	void write(const T& out) {

		//nullptr��������I��
		if (!Instance) {
			MessageBoxW(NULL, L"�R���\�[���I�u�W�F�N�g������܂���", L"err", MB_ICONERROR | MB_OK);
			return;
		}

		freopen_s(&fp, "CONOUT$", "w", stdout);		//�����\�ɂ���

		std::wcout << time_acquisition().c_str();

		std::wcout << L"| " << out << std::endl;

		freopen_s(&fp, "/dev/null", "w", stdout);	//�����֎~�ɂ���
	}

	//operator�ŏ�����
	template<typename T>
	void operator<<(const T& out) {
		write(out);
	}

};

Console* Console::Instance = nullptr;
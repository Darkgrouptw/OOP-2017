#include "DirectoryManager.h"
#include "ReportManager.h"


int main(int argv, char ** argc)
{
	#pragma region �ˬd�O�_�������|�Ѽ�
	if (argv != 2)
	{
		cout << "��J�榡���~" << endl;
		cout << "EX: 'OOP Checker'  �ɮץؿ�" << endl;
		return 0;
	}
	#pragma endregion
	#pragma region ��l�Ʃw�q
	ReportManager *rm = new ReportManager();
	#pragma endregion

	DirectoryManager::FindAllFileInDirectory(rm);
	return 0;
}
/*QProcess exe;
exe.start("foo.exe");
exe.write("uci");
exe.waitForReadyRead();
auto result = exe.readAll();*/
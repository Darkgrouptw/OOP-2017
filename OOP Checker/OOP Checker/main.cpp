#include "DirectoryManager.h"
#include "ReportManager.h"

#include <Windows.h>

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
	#pragma region ��l�Ƴ]�w
	system("cls");

	ReportManager		*rm = new ReportManager();
	QVector<QString>	FileList;
	#pragma endregion
	#pragma region �}�l�ˬd�ؿ�
	QString filePath(argc[1]);
	QDir dir(filePath);
	if (!dir.exists())
	{
		cout << "��Ƨ����s�b!!" << endl;
		return 0;
	}

	FileList = DirectoryManager::FindAllFileInDirectory(rm, QString(argc[1]));
	#pragma endregion
	rm->PrintReport();
	return 0;
}
/*QProcess exe;
exe.start("foo.exe");
exe.write("uci");
exe.waitForReadyRead();
auto result = exe.readAll();*/
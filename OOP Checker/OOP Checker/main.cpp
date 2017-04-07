#include "DirectoryManager.h"
#include "ReportManager.h"

#include <Windows.h>

int main(int argv, char ** argc)
{
	#pragma region 檢查是否有給路徑參數
	if (argv != 2)
	{
		cout << "輸入格式錯誤" << endl;
		cout << "EX: 'OOP Checker'  檔案目錄" << endl;
		return 0;
	}
	#pragma endregion
	#pragma region 初始化設定
	system("cls");

	ReportManager		*rm = new ReportManager();
	QVector<QString>	FileList;
	#pragma endregion
	#pragma region 開始檢查目錄
	QString filePath(argc[1]);
	QDir dir(filePath);
	if (!dir.exists())
	{
		cout << "資料夾不存在!!" << endl;
		return 0;
	}

	FileList = DirectoryManager::FindAllFileInDirectory(rm, QString(argc[1]));
	rm->PrintFileReport();
	#pragma endregion
	#pragma region 解壓縮到改的目錄
	DirectoryManager::UnzipFile(rm, filePath);
	#pragma endregion

	return 0;
}
/*QProcess exe;
exe.start("foo.exe");
exe.write("uci");
exe.waitForReadyRead();
auto result = exe.readAll();*/
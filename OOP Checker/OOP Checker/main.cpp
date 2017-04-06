#include "DirectoryManager.h"
#include "ReportManager.h"


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
	#pragma region 初始化定義
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
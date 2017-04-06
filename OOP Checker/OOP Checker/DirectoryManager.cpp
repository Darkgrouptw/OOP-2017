#include "DirectoryManager.h"

QVector<QString> DirectoryManager::FindAllFileInDirectory(ReportManager *rm)
{
	QVector<QString> list;
	QDir dir("./");
	QStringList strList = dir.entryList();

	// 刪除 . & ..


	cout << "========== 檔案管理 ==========" << endl;
	cout << "Length: " << strList.length() << endl;

	for (int i = 0; i < strList.length(); i++)
	{
		cout << strList[i].toStdString() << endl;
	}
	return list;
}

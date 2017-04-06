#include "DirectoryManager.h"

QVector<QString> DirectoryManager::FindAllFileInDirectory(ReportManager *rm, QString filePath)
{
	QVector<QString> list;
	QDir dir("./" + filePath);
	QStringList strList = dir.entryList();

	// 刪除 . & .. (前面兩個)
	strList.removeAt(1);
	strList.removeAt(0);

	for (int i = 0; i < strList.length(); i++)
	{
		//QString tempFileName = strList[i]
		if (!CheckIsCorrectFile(strList[i], filePath))
		{
			rm->AddWrongFile(strList[i]);
			continue;
		}
		/*else if (!CheckIsPastFile(strList[i]))
		{
			rm->AddPastFile(strList[i]);
			continue;
		}*/
		rm->AddCurrentFile(strList[i]);
		//cout << strList[i].toStdString() << endl;
	}
	return list;
}

bool DirectoryManager::CheckIsCorrectFile(QString &fileName, QString filePath)
{
	// 第一個字為 B or b
	if (fileName[0] == 'b')
	{
		QFile file("./" + filePath + "/" + fileName);
		fileName[0] = 'B';
		file.rename("./" + filePath + "/" + fileName);
	}
	else if (fileName[0] != 'B')
		return false;

	// 把所有超過只有學號的拿出來
	QStringList nameInfo = fileName.split(".");
	QStringList fileNameList = nameInfo[0].split("_");

	QString numberPart = fileNameList[0].mid(1, fileNameList[0].length() - 1);
	bool IsNumber = false;
	numberPart.toInt(&IsNumber);

	if (fileNameList[0].length() != QString("B10215035").length())
		return false;
	else if (!IsNumber)																								// 中間那段不是數字
		return false;
	else if (nameInfo[1].toLower() != "zip" && nameInfo[1].toLower() != "7z" && nameInfo[1].toLower() != "rar")		// 刪除非壓縮檔的
		return false;
	else if (nameInfo.length() > 2)																					// 刪除 B10215035.HW6.rar
		return false;
	else if (fileNameList.length() > 1)
	{
		if (fileNameList[1].mid(0, 2) != "HW" && fileNameList[1].mid(0, 3).toLower() != "ver")
			return false;
		else if (fileNameList.length() > 2)
				if (fileNameList[2].mid(0, 3).toLower() != "ver")
					return false;
	}
	return true;
}
bool DirectoryManager::CheckIsPastFile(QString fileName)
{
	QStringList strlist = fileName.split(".");
	QStringList nameInfo = strlist[0].split("_");

	// B10215035_HW6.rar or B10215035_HW6_ver1
	if (nameInfo.length() <= 1)
		return false;
	if (nameInfo[1].length() <= 2)
		return false;
	if (nameInfo[1].mid(0, 2) != "HW")
		return false;
	return true;
}

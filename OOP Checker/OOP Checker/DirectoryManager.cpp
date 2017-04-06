#include "DirectoryManager.h"

QVector<QString> DirectoryManager::FindAllFileInDirectory(ReportManager *rm, QString filePath)
{
	QVector<QString> list;
	QDir dir(filePath);
	QStringList strList = dir.entryList();

	// 刪除 . & .. (前面兩個)
	strList.removeAt(1);
	strList.removeAt(0);

	int week = filePath.mid(4, 2).toInt();
	rm->SetCurrentWeek(week);

	// 把錯誤檔案 & 別的作業的答案清掉，並把所有的其他的檔名拿出來，要做是否要其他 ver 的判斷
	QVector<QString> currentList, pastList;
	for (int i = 0; i < strList.length(); i++)
	{
		if (!CheckIsCorrectFile(strList[i], filePath, week))
		{
			rm->AddWrongFile(strList[i]);
			continue;
		}
		else if (CheckIsPastFile(strList[i]))
		{
			pastList.push_back(strList[i]);
			continue;
		}
		currentList.push_back(strList[i]);
	}

#pragma region 判斷 Current 的 Ignore 部分
	QVector<QString> *noignoreList = new QVector<QString>();
	QVector<QString> *ignoreList = new QVector<QString>();
	GetLatestVersionFile(currentList, noignoreList, ignoreList);
	for (int i = 0; i < noignoreList->length(); i++)
		rm->AddCurrentFile((*noignoreList)[i]);
	for (int i = 0; i < ignoreList->length(); i++)
		rm->AddIgnoreFile((*ignoreList)[i]);
#pragma endregion
#pragma region 判斷 Past 的 Ignore 部分
	(*noignoreList).clear();
	(*ignoreList).clear();
	GetLatestVersionFile(pastList, noignoreList, ignoreList);
	for (int i = 0; i < noignoreList->length(); i++)
		rm->AddPastFile((*noignoreList)[i]);
	for (int i = 0; i < ignoreList->length(); i++)
		rm->AddIgnoreFile((*ignoreList)[i]);
#pragma endregion
	return list;
}

bool DirectoryManager::CheckIsCorrectFile(QString &fileName, QString filePath, int week)
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
	if (!IsNumber)																								// 中間那段不是數字
		return false;
	if (nameInfo[1].toLower() != "zip" && nameInfo[1].toLower() != "7z" && nameInfo[1].toLower() != "rar")		// 刪除非壓縮檔的
		return false;
	if (nameInfo.length() > 2)																					// 刪除 B10215035.HW6.rar
		return false;
	if (fileNameList.length() > 1)
	{
		if (fileNameList[1].mid(0, 2) != "HW" && fileNameList[1].mid(0, 3).toLower() != "ver")
			return false;
		if (fileNameList[1].mid(0, 2) == "HW")																	// 刪除所有本周 但是還有 HW 開頭的
		{	
			bool IsOk = false;
			int tempWeek = fileNameList[1].mid(2, fileNameList[1].length() - 2).toInt(&IsOk);
			if (!IsOk || week == tempWeek)
				return false;
		}
		if (fileNameList[1].length() > 3)																		// 判斷除了是 ver 以外，還判斷後面的字可不可以轉乘 int
		{
			if (fileNameList[1].mid(0, 3).toLower() == "ver")
			{
				bool IsOk = false;
				fileNameList[1].mid(3, fileNameList[1].length() - 3).toInt(&IsOk);
				if (!IsOk)
					return false;
			}
		}
		if (fileNameList.length() > 2)
				if (fileNameList[2].mid(0, 3).toLower() != "ver")
					return false;
				else if (fileNameList[2].length() > 3)																// 判斷除了是 ver 以外，還判斷後面的字可不可以轉乘 int
				{
					if (fileNameList[2].mid(0, 3).toLower() == "ver")
					{
						bool IsOk = false;
						fileNameList[2].mid(3, fileNameList[2].length() - 3).toInt(&IsOk);
						if (!IsOk)
							return false;
					}
				}
				
	}
	return true;
}
bool DirectoryManager::CheckIsPastFile(QString fileName)
{
	QStringList strlist = fileName.split(".");
	QStringList nameInfo = strlist[0].split("_");

	// B10215035_HW6.rar or B10215035_HW6_ver1
	if (nameInfo.length() == 1)													// 無底線
		return false;
	else if (nameInfo[1].mid(0, 2) != "HW")
		return false; 
	return true;
}
void DirectoryManager::GetLatestVersionFile(QVector<QString> list, QVector<QString> *noignore, QVector<QString> *ignore)
{
	int index = 0;
	QString LastStuNumber, StuNumber, tempText;
	QVector<QString> tempList;														// 檔案名稱 (完整的)
	QVector<QString> versionList;													// 版本資訊
	while (index < list.length())
	{
		QStringList nameInfo = list[index].split(".");
		QStringList fileNameList = nameInfo[0].split("_");
		StuNumber = "";
		for (int i = 0 ; i < fileNameList.length(); i++)							// 要把 HW 幾也包刮進去
			if (!fileNameList[i].toLower().contains("ver"))
				StuNumber += fileNameList[i];

		// 如果不一樣的話，要先判對堆疊裡面有沒有超過一個東西，最後再把堆疊清空
		if (StuNumber != LastStuNumber)
		{
			if (tempList.size() > 1)
			{
				int MaxVersion = 0, MaxIndex = 0;
				for (int i = 0; i < tempList.size(); i++)
				{
					tempText = versionList[i].toLower().replace("ver", "");
					if (versionList[i] == "")
						continue;
					else
						if (MaxVersion < tempText.toInt())
						{
							MaxVersion = tempText.toInt();
							MaxIndex = i;
						}
				}

				// 找到最大的 index 之後把其他的加進 ignore　裡面
				for (int i = 0; i < tempList.size(); i++)
					if (MaxIndex != i)
						ignore->push_back(tempList[i]);
					else
						noignore->push_back(tempList[i]);
			}
			else if (tempList.size() != 0)
				noignore->push_back(tempList[0]);

			tempList.clear();
			versionList.clear();
		}

		// 每次都要把結果加進來
		tempList.push_back(list[index]);
		tempText = fileNameList[fileNameList.length() - 1];
		if (tempText.length() > 3)										// 有沒有超過 ver 這三個字 
		{
			if (tempText.mid(0, 3).toLower() == "ver")
				versionList.push_back(tempText);
			else
				versionList.push_back("");
		}
		else
			versionList.push_back("");
		LastStuNumber = StuNumber;
		index++;
	}

	// 最後還要再做一次判斷
	if (tempList.size() != 1)
	{
		int MaxVersion = 0, MaxIndex = 0;
		for (int i = 0; i < tempList.size(); i++)
			if (versionList[i] == "")
				continue;
			else
			{
				tempText = versionList[i].toLower().replace("ver", "");
				if (MaxVersion < tempText.toInt())
				{
					MaxVersion = tempText.toInt();
					MaxIndex = i;
				}
			}

		// 找到最大的 index 之後把其他的加進 ignore　裡面
		for (int i = 0; i < tempList.size(); i++)
			if (MaxIndex != i)
				ignore->push_back(tempList[i]);
			else
				noignore->push_back(tempList[i]);
	}
	else
		noignore->push_back(tempList[0]);
}
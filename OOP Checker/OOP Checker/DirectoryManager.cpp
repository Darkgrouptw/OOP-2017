#include "DirectoryManager.h"

QVector<QString> DirectoryManager::FindAllFileInDirectory(ReportManager *rm, QString filePath)
{
	QVector<QString> list;
	QDir dir(filePath);
	QStringList strList = dir.entryList();

	// �R�� . & .. (�e�����)
	strList.removeAt(1);
	strList.removeAt(0);

	int week = filePath.mid(4, 2).toInt();
	rm->SetCurrentWeek(week);

	// ����~�ɮ� & �O���@�~�����ײM���A�ç�Ҧ�����L���ɦW���X�ӡA�n���O�_�n��L ver ���P�_
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

#pragma region �P�_ Current �� Ignore ����
	QVector<QString> *noignoreList = new QVector<QString>();
	QVector<QString> *ignoreList = new QVector<QString>();
	GetLatestVersionFile(currentList, noignoreList, ignoreList);
	for (int i = 0; i < noignoreList->length(); i++)
		rm->AddCurrentFile((*noignoreList)[i]);
	for (int i = 0; i < ignoreList->length(); i++)
		rm->AddIgnoreFile((*ignoreList)[i]);
#pragma endregion
#pragma region �P�_ Past �� Ignore ����
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
	// �Ĥ@�Ӧr�� B or b
	if (fileName[0] == 'b')
	{
		QFile file("./" + filePath + "/" + fileName);
		fileName[0] = 'B';
		file.rename("./" + filePath + "/" + fileName);
	}
	else if (fileName[0] != 'B')
		return false;

	// ��Ҧ��W�L�u���Ǹ������X��
	QStringList nameInfo = fileName.split(".");
	QStringList fileNameList = nameInfo[0].split("_");

	QString numberPart = fileNameList[0].mid(1, fileNameList[0].length() - 1);
	bool IsNumber = false;
	numberPart.toInt(&IsNumber);

	if (fileNameList[0].length() != QString("B10215035").length())
		return false;
	if (!IsNumber)																								// �������q���O�Ʀr
		return false;
	if (nameInfo[1].toLower() != "zip" && nameInfo[1].toLower() != "7z" && nameInfo[1].toLower() != "rar")		// �R���D���Y�ɪ�
		return false;
	if (nameInfo.length() > 2)																					// �R�� B10215035.HW6.rar
		return false;
	if (fileNameList.length() > 1)
	{
		if (fileNameList[1].mid(0, 2) != "HW" && fileNameList[1].mid(0, 3).toLower() != "ver")
			return false;
		if (fileNameList[1].mid(0, 2) == "HW")																	// �R���Ҧ����P ���O�٦� HW �}�Y��
		{	
			bool IsOk = false;
			int tempWeek = fileNameList[1].mid(2, fileNameList[1].length() - 2).toInt(&IsOk);
			if (!IsOk || week == tempWeek)
				return false;
		}
		if (fileNameList[1].length() > 3)																		// �P�_���F�O ver �H�~�A�٧P�_�᭱���r�i���i�H�୼ int
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
				else if (fileNameList[2].length() > 3)																// �P�_���F�O ver �H�~�A�٧P�_�᭱���r�i���i�H�୼ int
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
	if (nameInfo.length() == 1)													// �L���u
		return false;
	else if (nameInfo[1].mid(0, 2) != "HW")
		return false; 
	return true;
}
void DirectoryManager::GetLatestVersionFile(QVector<QString> list, QVector<QString> *noignore, QVector<QString> *ignore)
{
	int index = 0;
	QString LastStuNumber, StuNumber, tempText;
	QVector<QString> tempList;														// �ɮצW�� (���㪺)
	QVector<QString> versionList;													// ������T
	while (index < list.length())
	{
		QStringList nameInfo = list[index].split(".");
		QStringList fileNameList = nameInfo[0].split("_");
		StuNumber = "";
		for (int i = 0 ; i < fileNameList.length(); i++)							// �n�� HW �X�]�]��i�h
			if (!fileNameList[i].toLower().contains("ver"))
				StuNumber += fileNameList[i];

		// �p�G���@�˪��ܡA�n���P����|�̭����S���W�L�@�ӪF��A�̫�A����|�M��
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

				// ���̤j�� index ������L���[�i ignore�@�̭�
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

		// �C�����n�⵲�G�[�i��
		tempList.push_back(list[index]);
		tempText = fileNameList[fileNameList.length() - 1];
		if (tempText.length() > 3)										// ���S���W�L ver �o�T�Ӧr 
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

	// �̫��٭n�A���@���P�_
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

		// ���̤j�� index ������L���[�i ignore�@�̭�
		for (int i = 0; i < tempList.size(); i++)
			if (MaxIndex != i)
				ignore->push_back(tempList[i]);
			else
				noignore->push_back(tempList[i]);
	}
	else
		noignore->push_back(tempList[0]);
}
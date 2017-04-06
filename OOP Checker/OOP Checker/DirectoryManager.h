#pragma once
#include "ReportManager.h"

#include <iostream>

#include <QDir>
#include <QVector>
#include <QString>
#include <QStringList>

using namespace std;

class DirectoryManager
{
public:
	static QVector<QString> FindAllFileInDirectory(ReportManager *, QString);								// Chase 整個 Directory

	static bool				CheckIsCorrectFile(QString &, QString);											// 確定檔案名稱是否正確，如果有小寫的話(b10215035)，改成大寫(B10215035)
	static bool				CheckIsPastFile(QString);														// 判對是否是過去的檔案
};


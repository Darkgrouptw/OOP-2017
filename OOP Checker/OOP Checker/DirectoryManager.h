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
	static QVector<QString> FindAllFileInDirectory(ReportManager *, QString);								// Chase ��� Directory

	static bool				CheckIsCorrectFile(QString &, QString);											// �T�w�ɮצW�٬O�_���T�A�p�G���p�g����(b10215035)�A�令�j�g(B10215035)
	static bool				CheckIsPastFile(QString);														// �P��O�_�O�L�h���ɮ�
};


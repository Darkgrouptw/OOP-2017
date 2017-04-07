#pragma once
#include "ReportManager.h"

#include <iostream>

#include <QDir>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QThread>

#include <QProcess>
//#include <Windows.h>

using namespace std;

class DirectoryManager
{
public:
	static QVector<QString> FindAllFileInDirectory(ReportManager *, QString);								// Chase ��� Directory
	static void				UnzipFile(ReportManager *, QString);

	static bool				CheckIsCorrectFile(QString &, QString, int);									// �T�w�ɮצW�٬O�_���T�A�p�G���p�g����(b10215035)�A�令�j�g(B10215035)
	static bool				CheckIsPastFile(QString);														// �P��O�_�O�L�h���ɮ�
	static void				GetLatestVersionFile(QVector<QString>, QVector<QString> *, QVector<QString>* );	// ��X�̷s���ɮ�
};


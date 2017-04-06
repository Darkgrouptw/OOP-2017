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
	static QVector<QString> FindAllFileInDirectory(ReportManager *);
};


#pragma once
#include <iostream>

#include <QVector>
#include <QString>

using namespace std;

class ReportManager
{
public:
	ReportManager();
	~ReportManager();

	void				SetFileRoot(QString);														// 設定檔案的 root 位置
	void				SetCurrentWeek(int);														// 設定今天第幾周
	void				AddCurrentFile(QString);													// 增加 Current File
	void				AddIgnoreFile(QString);														// 增加 Ignore File
	void				AddPastFile(QString);														// 增加 Past File
	void				AddWrongFile(QString);														// 增加 Wrong File

	void				PrintReport();																// 把所有的 Report 印出來
private:
	int					week;																		// 這周第幾周
	QString				FileRoot;																	// 現在這一周的檔案位置
	QVector<QString>	CurrentFileList;															// 現在這周的作業
	QVector<QString>	IgnoreFileList;																// 現在這一周，但是不是最新的檔案 (ver)
	QVector<QString>	PastFileList;																// 不是這一周的檔案
	QVector<QString>	WrongFileList;																// 錯誤的檔案名稱
};

/*
輸出文件：
1. 一份所有成績的報告
2. 還有 N 個每個同學的報告
*/

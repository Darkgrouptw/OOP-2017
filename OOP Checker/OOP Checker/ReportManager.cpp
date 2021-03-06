#include "ReportManager.h"

void ReportManager::SetFileRoot(QString root)
{
	this->FileRoot = root;
}
void ReportManager::SetCurrentWeek(int week)
{
	this->week = week;
}
void ReportManager::AddCurrentFile(QString tempCheck)
{
	CurrentFileList.push_back(tempCheck);
}
void ReportManager::AddIgnoreFile(QString tempIgnore)
{
	IgnoreFileList.push_back(tempIgnore);
}
void ReportManager::AddPastFile(QString tempPast)
{
	this->PastFileList.push_back(tempPast);
}
void ReportManager::AddWrongFile(QString tempWrong)
{
	this->WrongFileList.push_back(tempWrong);
}

QVector<QString> ReportManager::GetCurrentFileList()
{
	return this->CurrentFileList;
}
QVector<QString> ReportManager::GetIgnoreFileList()
{
	return this->IgnoreFileList;
}
QVector<QString> ReportManager::GetPastFileList()
{
	return this->PastFileList;
}
QVector<QString> ReportManager::GetWrongFileList()
{
	return this->WrongFileList;
}

void ReportManager::PrintFileReport()
{
	cout << "Week" << QString::number(week).rightJustified(2, '0').toStdString() << endl;
	cout << "Total =>" << (CurrentFileList.length() + IgnoreFileList.length() + PastFileList.length() + WrongFileList.length()) << endl;

	cout << "========== Current File ==========" << endl;
	cout << "Size => " << CurrentFileList.length() << endl;
	for (int i = 0; i < CurrentFileList.length(); i++)
		cout << CurrentFileList[i].toStdString() << endl;

	cout << "========== Ignore File ==========" << endl;
	cout << "Size => " << IgnoreFileList.length() << endl;
	for (int i = 0; i < IgnoreFileList.length(); i++)
		cout << IgnoreFileList[i].toStdString() << endl;

	cout << "========== Past File ==========" << endl;
	cout << "Size => " << PastFileList.length() << endl;
	for (int i = 0; i < PastFileList.length(); i++)
		cout << PastFileList[i].toStdString() << endl;

	cout << "========== Wrong File ==========" << endl;
	cout << "Size => " << WrongFileList.length() << endl;
	for (int i = 0; i < WrongFileList.length(); i++)
		cout << WrongFileList[i].toStdString() << endl;
}

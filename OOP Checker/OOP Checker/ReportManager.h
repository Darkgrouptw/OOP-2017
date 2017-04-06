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

	void				SetFileRoot(QString);														// �]�w�ɮת� root ��m
	void				SetCurrentWeek(int);														// �]�w���ѲĴX�P
	void				AddCurrentFile(QString);													// �W�[ Current File
	void				AddIgnoreFile(QString);														// �W�[ Ignore File
	void				AddPastFile(QString);														// �W�[ Past File
	void				AddWrongFile(QString);														// �W�[ Wrong File

	void				PrintReport();																// ��Ҧ��� Report �L�X��
private:
	int					week;																		// �o�P�ĴX�P
	QString				FileRoot;																	// �{�b�o�@�P���ɮצ�m
	QVector<QString>	CurrentFileList;															// �{�b�o�P���@�~
	QVector<QString>	IgnoreFileList;																// �{�b�o�@�P�A���O���O�̷s���ɮ� (ver)
	QVector<QString>	PastFileList;																// ���O�o�@�P���ɮ�
	QVector<QString>	WrongFileList;																// ���~���ɮצW��
};

/*
��X���G
1. �@���Ҧ����Z�����i
2. �٦� N �ӨC�ӦP�Ǫ����i
*/

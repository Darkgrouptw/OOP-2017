#pragma once
#include <QFile>
#include <QString>
#include <QThread>
#include <QProcess>
#include <QByteArray>

class CheckerThead : public QThread
{
	Q_OBJECT
public:
	CheckerThead(QString);
	~CheckerThead();

	void run();
private:
	QProcess exe;
	QString FileName;
};


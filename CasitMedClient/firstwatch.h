#ifndef FIRSTWATCH_H
#define FIRSTWATCH_H

#include <QObject>
#include <QThread>
#include <QFileInfoList>
#include <QStringList>
#include "datachange.h"

class firstwatch : public QThread
{
	Q_OBJECT

public:
	firstwatch();
	~firstwatch();
	void run();
	QFileInfoList GetFileList(QString path);
	QStringList findFiles(const QString &path);

private:
	datachange *_datachange;
	QStringList _qstringlist;
	QStringList tempFileNames;
public:
	QStringList qstringlist;
};

#endif // FIRSTWATCH_H

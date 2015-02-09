#ifndef WATCHFILEWATCH_H
#define WATCHFILEWATCH_H

#include "transferdatastore.h"
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QStringList>
#include <QSharedMemory>
#include <QBuffer>
#include <QMutex>

class watchFileWatch : public QThread
{
	Q_OBJECT

public:
	watchFileWatch();
	~watchFileWatch();
	void timerEvent(QTimerEvent *event);        /*定时器相应*/
	void run();
	void detch();

signals:
	void sendsignal();          //发现文件信号
	public slots:
		void acceptfile();             
		void loadFromStringList();
public:
	QStringList m_watchFile;
	QMutex m_qmutex;

private:
	QSharedMemory sharedMemory;
	transferdatastore *_transferdatastore;
	
};

#endif // WATCHFILEWATCH_H

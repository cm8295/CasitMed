/************************************************************************/
/*                     为主线程casitmedclient服务                       */
/************************************************************************/
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "casitmedclient.h"
#include "transferdatastore.h"
#include "filetransfer.h"
#include <QObject>
#include <QStringList>
#include <QThread>
#include <QSharedMemory>
#include <QBuffer>
#include <QMutex>
#include <QString>
#include <QProcess>
#include <QMessageBox>

using namespace std;

class mythread : public QThread
{
	Q_OBJECT

public:
	mythread();
	~mythread();
	void run();
	//void closeEvent(QCloseEvent *event);   /*系统关闭前触发的事件*/
	void timerEvent(QTimerEvent *event);        /*定时器相应*/
	void detach();
signals:
	void sentSignal();

public slots:
	void loadFromMemory();   //从内存中加载
	void transfer();
	void speedslot(int _speed); //接收速度信号的槽
	void filetransferokslot(QString);    //接收文件传输完成的槽

public:
	//QStringList m_getFileNames;
	QStringList m_fileInfoList;     //从数据库中读取数据信息列表，序号0：ID，1：相对路径文件名，2：绝对路径文件名，3：文件大小
private:
    QString filewatch;
	int _currentSpeed;
public:

private:
	QSharedMemory sharedMemory;
	CasitMedClient *m_casitmedclient;
	filetransfer *_filetransfer;
	QMutex m_qmutex;
	transferdatastore *_transferdatastore;
	QString _fileId;       //文件ID号
	QString _fileSize;     //文件大小
	QString _fileName;     //文件绝对路径
};

#endif // MYTHREAD_H

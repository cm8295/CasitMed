/************************************************************************/
/*                     Ϊ���߳�casitmedclient����                       */
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
	//void closeEvent(QCloseEvent *event);   /*ϵͳ�ر�ǰ�������¼�*/
	void timerEvent(QTimerEvent *event);        /*��ʱ����Ӧ*/
	void detach();
signals:
	void sentSignal();

public slots:
	void loadFromMemory();   //���ڴ��м���
	void transfer();
	void speedslot(int _speed); //�����ٶ��źŵĲ�
	void filetransferokslot(QString);    //�����ļ�������ɵĲ�

public:
	//QStringList m_getFileNames;
	QStringList m_fileInfoList;     //�����ݿ��ж�ȡ������Ϣ�б����0��ID��1�����·���ļ�����2������·���ļ�����3���ļ���С
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
	QString _fileId;       //�ļ�ID��
	QString _fileSize;     //�ļ���С
	QString _fileName;     //�ļ�����·��
};

#endif // MYTHREAD_H

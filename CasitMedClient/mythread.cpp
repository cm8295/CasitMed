#include "mythread.h"
#include <QtGlobal> 

mythread::mythread()
	: QThread()
{
	m_casitmedclient = new CasitMedClient();
	m_casitmedclient->show();
	_transferdatastore = new transferdatastore(this);
	_filetransfer = new filetransfer(this);
	int _currentSpeed = 0; 
	connect(this,SIGNAL(sentSignal()),this,SLOT(transfer()));
	// 设置key，系统用它作为底层共享内存段的标识
	sharedMemory.setKey("QSharedMemoryCasit");
	connect(m_casitmedclient, SIGNAL(speedsignal(int)), this, SLOT(speedslot(int)));
	//connect(_firstwatch, SIGNAL(firstwatchsignal(QStringList)), this, SLOT(firstwatchslot(QStringList)));
	/****************************************定时器***********************************************/
	startTimer(3000);
	/*********************************************************************************************/
}

void mythread::run()
{
	//connect(m_casitmedclient, SIGNAL(transferOksignal(QString)), this, SLOT(filetransferokslot(QString)));
	//filetransferokslot("");
	m_fileInfoList.clear();
	m_fileInfoList.append(_transferdatastore->finddatasqlite("upload_file"));
	_fileName = m_fileInfoList[2];
	_filetransfer->filetransferExternalInterface(m_casitmedclient->m_watchpath, _fileName);
	exec();
}

void mythread::loadFromMemory()
{
	if (!sharedMemory.attach()) {
		return;
	}
	QBuffer buffer;
	QDataStream in(&buffer);
	QStringList strss;
	sharedMemory.lock();
	buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
	buffer.open(QBuffer::ReadOnly);
	in >> strss;
	if(filewatch == strss[0])
	{
		sharedMemory.unlock();
		sharedMemory.detach();
		return;
	}
	else
	{
		filewatch = strss[0];
	}
	m_qmutex.lock();
	m_casitmedclient->m_getOpenFileNames.append(strss);
	m_qmutex.unlock();
	sharedMemory.unlock();
	sharedMemory.detach();
}

void mythread::detach()
{
	if (!sharedMemory.detach())
	{

	}
}

void mythread::timerEvent(QTimerEvent *event)  //未使用方法
{
	if(!m_casitmedclient->blIsTransfer)
	{
		//filetransferokslot("");
	}
}

void mythread::transfer()
{
	if(!m_casitmedclient->blIsTransfer && m_casitmedclient->fileNames.isEmpty())
	{
		m_casitmedclient->transfer();
	}
}

void mythread::speedslot(int _speed)
{
	m_qmutex.lock();
	_currentSpeed += _speed;
	m_qmutex.unlock();
}

void mythread::filetransferokslot(QString _transferInfo)
{
	if(_transferInfo == "deletefile")
	{
		_transferdatastore->deletedatasqlite("upload_file",m_casitmedclient->m_fileId);
		return;
	}
	m_fileInfoList.clear();
	m_fileInfoList.append(_transferdatastore->finddatasqlite("upload_file"));
	if (m_fileInfoList[0].isEmpty())
	{
		m_casitmedclient->m_transferSpeed = _currentSpeed;
		m_qmutex.lock();
		_currentSpeed = 0;
		m_qmutex.unlock();
		return;
	} 
	//else if(_fileId!=m_fileInfoList[0])
	//{
	//	_fileId = m_fileInfoList[0];
	//	_fileSize = m_fileInfoList[3];
	//	m_casitmedclient->m_fileId = _fileId.toInt();
	//	//m_casitmedclient->m_getOpenFileNames.append(m_fileInfoList[2]);
	//	m_casitmedclient->m_filePathName = m_fileInfoList[2];
	//	//m_casitmedclient->m_filesize += _fileSize.toInt();
	//	//emit sentSignal();
	//	m_casitmedclient->transfer();
	//}
	//else
	//{
	//	m_casitmedclient->m_transferSpeed = _currentSpeed;
	//	m_qmutex.lock();
	//	_currentSpeed = 0;
	//	m_qmutex.unlock();
	//}
	_fileId = m_fileInfoList[0];
	_fileSize = m_fileInfoList[3];
	m_casitmedclient->m_fileId = _fileId.toInt();
	m_casitmedclient->m_filePathName = m_fileInfoList[2];
	//m_casitmedclient->m_filesize += _fileSize.toInt();
	//emit sentSignal();
	m_casitmedclient->transfer();
}

mythread::~mythread()
{

}

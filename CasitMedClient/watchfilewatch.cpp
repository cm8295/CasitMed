#include "watchfilewatch.h"


watchFileWatch::watchFileWatch()
	: QThread()
{
	startTimer(3000);    //每隔10S监测一次
	// 设置key，系统用它作为底层共享内存段的标识
	sharedMemory.setKey("QSharedMemoryCasit");
	_transferdatastore = new transferdatastore(this);
	connect(this,SIGNAL(sendsignal()),this,SLOT(acceptfile()));
}

void watchFileWatch::run()
{
	exec();
}

void watchFileWatch::acceptfile()
{
	//loadFromStringList();
	if(m_watchFile.isEmpty())
	{
		return;
	}
	for(int i = 0; m_watchFile.count() > 0; )
	{
		_transferdatastore->insertdatasqlite("upload_file","",m_watchFile.at(i),0);
		m_watchFile.removeAt(i);
	}
}

void watchFileWatch::loadFromStringList()
{
	QBuffer buffer;
	buffer.open(QBuffer::ReadWrite);
	QDataStream out(&buffer);
	out << m_watchFile;
	m_watchFile.clear();  //清除数据
	int size = buffer.size();
	if (!sharedMemory.create(size)) {
		//ui->label->setText(tr("无法创建共享内存段！"));
		return;
	}
	sharedMemory.lock();
	char *to = (char*)sharedMemory.data();
	const char *from = buffer.data().data();
	memcpy(to, from, qMin(sharedMemory.size(), size));
	sharedMemory.unlock();
}

void watchFileWatch::detch()
{
	if(!sharedMemory.detach())
	{

	}
}

watchFileWatch::~watchFileWatch()
{

}

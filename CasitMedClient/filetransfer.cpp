#include "filetransfer.h"

filetransfer::filetransfer(QObject *parent)
	: QObject(parent)
{
	tcpClient = new QTcpSocket();
}

filetransfer::~filetransfer()
{

}

void filetransfer::filetransferExternalInterface(QString _watchpath, QString _filename)
{
	m_watchpath = _watchpath;
	m_fileName = _filename;
	start();
}

void filetransfer::start()  //激活
{  
	loadSize = 4*1024;  
	TotalBytes = 0;  
	bytesWritten = 0;  
	bytesToWrite = 0;  
	isOpenFile = true;
	tcpClient->connectToHost(QHostAddress("192.168.1.77"),19842);  
	connect(tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));  
	connect(tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));  
	connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError))); 
}  

void filetransfer::startTransfer()  
{   
	localFile = new QFile(m_fileName);  
	if(!localFile->open(QFile::ReadOnly))  
	{  
		/*QMessageBox::warning(this,tr("Application"),  
			tr("can not open %1:\n%2.")  
			.arg(m_fileName)  
			.arg(localFile->errorString())); */ 
		return;  
	}  
	blIsopenfile = true;
	TotalBytes = localFile->size();  
	QDataStream sendOut(&outBlock,QIODevice::WriteOnly);  
	sendOut.setVersion(QDataStream::Qt_4_7);  
	//QString currentFile = m_fileName.right(m_fileName.size()-  
	//	m_fileName.lastIndexOf('/')-1);        //.right出去文件路径部分，仅将文件部分保存在currentFile中
	QStringList currentFilelist = m_fileName.split(m_watchpath.replace('\\','/') + '/');
	QString currentFile = currentFilelist[1];
	sendOut<<qint64(0)<<qint64(0)<<currentFile;  //构造一个临时的文件头
	TotalBytes += outBlock.size();  //获得文件头的实际存储大小
	sendOut.device()->seek(0);  //将读写操作指向从头开始
	sendOut<<TotalBytes<<qint64(outBlock.size()- sizeof(qint64)*2);  
	bytesToWrite = TotalBytes - tcpClient->write(outBlock);  
	qDebug()<<currentFile<<TotalBytes;  
	outBlock.resize(0);  
}  

void filetransfer::updateClientProgress(qint64 numBytes)  
{  
	bytesWritten += (int)numBytes;  
	if(bytesToWrite > 0)  
	{  
		if(bytesToWrite > 0)  
		{  
			outBlock = localFile->read(qMin(bytesToWrite,loadSize));  
			bytesToWrite -= (int)tcpClient->write(outBlock);  
			outBlock.resize(0);  
		}  
		else  
		{  
			if(blIsopenfile)
			{
				localFile->close(); 
				blIsopenfile = false;
			}
		}  
	}  
	//ui.clientProgressBar->setMaximum(TotalBytes);  
	//ui.clientProgressBar->setValue(bytesWritten);  
	//ui.clientStatusLabel->setText(tr("Have send %1KB").arg(bytesWritten/(1024)));  
	if(bytesWritten == TotalBytes)
	{
		isOpenFile = true;
		if(blIsopenfile)
		{
			localFile->close(); 
			blIsopenfile = false;
		}
		tcpClient->abort();
	}
}  

void filetransfer::displayError(QAbstractSocket::SocketError socketError)  
{  
	if(socketError == QTcpSocket::RemoteHostClosedError)  
		return;  
	/*QMessageBox::information(this,tr("NetWork"),  
	tr("generate the following error:%1.")  
	.arg(tcpClient.errorString())); */
	if(blIsopenfile)
	{
		localFile->close();
		blIsopenfile = false;
	}
	tcpClient->close();  
	//ui.clientProgressBar->reset();  
	//ui.clientStatusLabel->setText(tr("Client has been ready"));  
	//ui.startButton->setEnabled(true);  
	emit transferErrorSignal(m_fileName,0,"Net Error");
} 


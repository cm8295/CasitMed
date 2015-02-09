#include "casitmedclient.h"
#include <QtGlobal>  

CasitMedClient::CasitMedClient(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_netwatch = new netwatch();
	_netwatch->start();

	_transferdatastore = new transferdatastore(this);
	_transferdatastore->createconnectsqlite("CasitFileInformationStore.db");
	//_transferdatastore->insertAlldatasqlite("upload_history_file",m_getOpenFileNames);
	//_transferdatastore->insertdatasqlite("upload_file","a/b/ce/d/d.txt","c:/a/b/c/d.txt",5023);
	//_transferdatastore->finddatasqlite("upload_file");
	//_transferdatastore->deletedatasqlite("upload_file",1);
	//
	qlistmodel = new QStringListModel(m_notUpLoad);
	ui.lvShowView->setModel(qlistmodel);
	qlistmodelOk = new QStringListModel(fileNamesOk);
	ui.lvShowOk->setModel(qlistmodelOk);
	//
	//m_serverIp = "118.122.250.117";    //公司IP
	//m_serverIp = "192.168.1.77";     //测试Ip
	m_serverIp = "192.168.1.45";     //测试Ip
	m_serverPort = 19842;
	blIsTransfer = false;
	/*                           拖曳                                       */
	//ui.lineEdit->setAcceptDrops(false);
	//setAcceptDrops(true);
	/************************************************************************/
	/******************************* 界面设计********************************/
	ui.leDownLoad->setVisible(false);
	ui.downLoadButton->setVisible(false);
	//setFixedSize(553,411);
	//QPalette palette(this->palette());
	//palette.setColor(QPalette::Background, Qt::white);
	//this->setPalette(palette);
// 	setWindowOpacity(1);      
// 	setWindowFlags(Qt::FramelessWindowHint);      
// 	setAttribute(Qt::WA_TranslucentBackground); 

	//this->setWindowFlags(Qt::FramelessWindowHint);
	//this->setAttribute(Qt::WA_TranslucentBackground);
	//this->setMinimumSize(450,450);
	//设置窗体标题栏隐藏并设置位于顶层
	//setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setWindowFlags(Qt::FramelessWindowHint);
	//可获取鼠标跟踪效果
	setMouseTracking(true);
	ui.pbClose->setFlat(true);
	ui.pbMin->setFlat(true);
	ui.pbSet->setFlat(true);
	ui.centralWidget->setAutoFillBackground(true);
	QPalette palette;
	//palette.setColor(QPalette::Background, QColor(Qt::darkBlue));
	//palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
	ui.centralWidget->setPalette(palette);
	/************************************************************************/
	/************************************************************************/
	/*                           系统配置                                   */
	creatTrayIcon();
	systeminit();
	if(m_watchpath.length() <= 3)
	{
		QMessageBox::information(this,"提示！","不能选择监视根目录，请重新选择！");
		return;
	}
	systemsignalslotinit();   //信号和槽初始化
	//startProcess();              //启动监测文件程序
	/************************************************************************/
	/************************************************************************/
	/*                          修改路径文件监测                            */
	/************************************************************************/
	/*if(dataChange->valueReadINI() == "1")
	{
		_firstwatch = new firstwatch();
		_firstwatch->start();
		m_getOpenFileNames.append(_firstwatch->qstringlist);
		transfer();
	}
	dataChange->setwriteINI();*/
}

void CasitMedClient::systeminit()
{
	tcpSocket = new QTcpSocket;
	blockSize = 0;
	loadSize = 4*1024;  
	TotalBytes = 0;  
	bytesWritten = 0;  
	bytesToWrite = 0;  
	bytesReceived = 0;
	fileNameSize = 0;
	folderAllsize = 0;
	m_filesize = 0;
	m_signalFileSize = 0;
	m_transferSpeed = 0;
	isOpenFile = true;
	isDownFile = true;
	blfileHeader = true;
	blIsopenfile = false;
	blIsTransfer = false;
	m_watchpath = dataChange->readINI("");
	m_watchpath.replace('/','\\');
 	ui.leWatchPath->hide();
 	ui.pbWatchPath->hide();
	ui.pbSure->hide();
	
}

void CasitMedClient::systemsignalslotinit()
{
	connect(ui.downLoadButton,SIGNAL(clicked()),this,SLOT(downLoadFile()));
	connect(tcpSocket,SIGNAL(connectionClosed()),this,SLOT(connectClose()));
	//connect(ui.pbSet,SIGNAL(clicked()),this,SLOT(systemSet()));    
	connect(ui.pbClose,SIGNAL(clicked()),this,SLOT(close()));  
	connect(ui.pbMin,SIGNAL(clicked()),this,SLOT(minAction()));  
	connect(ui.pbSet,SIGNAL(clicked()),this,SLOT(creatSystemSetIni()));  
	connect(ui.pbWatchPath,SIGNAL(clicked()),this,SLOT(fileWatchPath()));  
	connect(ui.pbSure,SIGNAL(clicked()),this,SLOT(sureWatchPath()));  
}

void CasitMedClient::transfererror()
{
	qDebug()<<"传输错误";
}

void CasitMedClient::connectClose()
{
	qDebug()<<"连接错误";
}

void CasitMedClient::fileWatchPath()
{
	QString dirs = QFileDialog::getExistingDirectory(this,tr("浏览文件夹"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	ui.leWatchPath->setText(dirs);
}

void CasitMedClient::sureWatchPath()
{
	if(ui.leWatchPath->text().length() <= 3)
	{
		QMessageBox::information(this,"提示！","不能选择根目录，请重新选择！");
		return;
	}
	QFileInfo fileinfo(ui.leWatchPath->text());
	if(m_watchpath==ui.leWatchPath->text())
	{
		QMessageBox::information(this,"提示！","当前正在监视该文件夹！");
		ui.pbSure->hide();
		ui.leWatchPath->hide();
		ui.pbWatchPath->hide();
		return;
	}
	if(ui.leWatchPath->text().isEmpty())
	{
		QMessageBox::warning(NULL,"警告！","路径不能为空，请选择路径！");
		return;
	}
	if(fileinfo.exists() && fileinfo.isDir())
	{
		dataChange->writeINI(ui.leWatchPath->text());
		QMessageBox::information(this,"提示！","修改成功,重新启动程序生效");
		ui.pbSure->hide();
		ui.leWatchPath->hide();
		ui.pbWatchPath->hide();
	}
	else 
	{
		QMessageBox::warning(NULL,"警告！","请检查监视路径是否正确！");
		return;
	}
}

void CasitMedClient::transfer()
{
	if(!blIsTransfer)
	{
		//ui.lb1_2->setText(QString::number(m_getOpenFileNames.count()));
		//ui.lb1_4->setText(QString::number(m_getOpenFileNames.count()));
		/*foreach(QString str, m_getOpenFileNames)
		{
		m_notUpLoad.append(str.right(str.size() - str.lastIndexOf('/')-1));
		}
		qlistmodel->setStringList(m_notUpLoad);*/
		if(!m_filePathName.isEmpty())
		{
			m_qmutex.lock();
			fileNames.append(m_filePathName);
			m_qmutex.unlock();
		}
		//m_filesize = fileSize(fileNames);
		if(!blIsTransfer)
		{
			start();
		}
	}
	//if(!blIsTransfer)
	//{
	//	//ui.lb1_2->setText(QString::number(m_getOpenFileNames.count()));
	//	//ui.lb1_4->setText(QString::number(m_getOpenFileNames.count()));
	//	foreach(QString str, m_getOpenFileNames)
	//	{
	//		m_notUpLoad.append(str.right(str.size() - str.lastIndexOf('/')-1));
	//	}
	//	qlistmodel->setStringList(m_notUpLoad);
	//	if(!m_getOpenFileNames.isEmpty())
	//	{
	//		/*for(int i = 0; i<m_getOpenFileNames.count(); i++)
	//		{
	//			fileNames.append(m_getOpenFileNames.at(i));
	//			m_qmutex.lock();
	//			m_getOpenFileNames.removeAt(i);
	//			m_qmutex.unlock();
	//		}*/
	//		fileNames.append(m_getOpenFileNames);
	//		//QStringListModel *qlistmodel = new QStringListModel(m_getOpenFileNames);
	//		//ui.lvShowView->setModel(qlistmodel);
	//		m_getOpenFileNames.clear();
	//	}
	//	m_filesize = fileSize(fileNames);
	//	if(!blIsTransfer)
	//	{
	//		start();
	//	}
	//}
} 

void CasitMedClient::openFile()  
{  
	/*上传文件夹*/
	QString dirs = QFileDialog::getExistingDirectory(this,tr("浏览文件夹"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	QFileInfo qfileinfo = QFileInfo(dirs);
	if(qfileinfo.isDir())
	{
		findFiles(dirs);
		QStringListModel *qlistmodel = new QStringListModel(m_getOpenFileNames);
		ui.lvShowView->setModel(qlistmodel);
		storyPath = dirs.right(dirs.size() - dirs.lastIndexOf('\\') - 1);
		//ui.startButton->setEnabled(true); 
		//fileName = fileNames[0];
		//ui.openButton->setEnabled(false);
	}
}

/*通过拖曳获取文件路径*/
void CasitMedClient::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
	event->acceptProposedAction();
}

void CasitMedClient::dropEvent(QDropEvent *event)/*拖曳*/
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
	{
		return;
	}
	isOpenFile = true;
	foreach(QUrl url, urls)
	{
		QFileInfo fi;
		QString ftest = url.toLocalFile();
		fi = QFileInfo(ftest);
		if(fi.isDir())
		{
			findFiles(ftest);
		}
		else
		{
			fileNames.append(url.toLocalFile());
		}
	}
	QStringListModel *qmodel = new QStringListModel(fileNames);
	ui.lvShowView->setModel(qmodel);
	qmodel->setStringList(fileNames);
}

QStringList CasitMedClient::findFiles(const QString &path)
{
	QDir *fDir = new QDir(path);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(fDir->entryInfoList());
	int jj = fileInfo->count();
	int i;
	for(i = 0;i<fileInfo->count();i++)
	{
		if(fileInfo->at(i).fileName()=="."|fileInfo->at(i).fileName()=="..")
		{
			i++;
			continue;
		}
		if(fileInfo->at(i).isDir())
		{
			tempFileNames.append(fileInfo->at(i).filePath());
			continue;
		}
		m_getOpenFileNames.append(fileInfo->at(i).filePath());
	}
	for(int j = 0;j < tempFileNames.count();j++)
	{
		QString tempFile = tempFileNames[j];
		tempFileNames.removeAt(j);
		findFiles(tempFile);
	}
	return m_getOpenFileNames;
}

void CasitMedClient::start()  //激活
{  
	try
	{
		ui.lb1_4->setText(QString::number(fileNames.count()));
		ui.lbtransfer->setText("");
		isDownFile = false;
		blIsTransfer = true;
		blIsopenfile = false;
		loadSize = 4*1024;  
		TotalBytes = 0;  
		bytesWritten = 0;  
		bytesToWrite = 0;
		tcpSocket->abort();
		tcpSocket->connectToHost(QHostAddress(m_serverIp),m_serverPort);  
		connect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
		connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
		connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
			this,SLOT(displayError(QAbstractSocket::SocketError))); 
	}
	catch(QString err)
	{
		QMessageBox::information(this,"警告！","start err");
	}
}  

void CasitMedClient::startTransfer()  
{   
	try
	{
		blIsTransfer = true;
	    ui.lb1_4->setText(QString::number(fileNames.count()));
		ui.lbtransfer->setText("");
		if(isDownFile)
		{
			return;
		}
		//fileNames.append(_transferdatastore->finddatasqlite("upload_file")[2]);
		if(!fileNames.isEmpty())    //如果fileNames为空则退出
		{
			fileName = fileNames[0];
			QFileInfo qfileinfo = QFileInfo(fileName);
			while(!qfileinfo.isFile())
			{
				if(fileNames.count() > 1)
				{
					fileNames.removeAt(0);
					m_errUpLoad.append(m_notUpLoad.at(0));
					m_qmutex.lock();
					if (!m_notUpLoad.isEmpty())
					{
						m_notUpLoad.removeAt(0);
					}
					m_qmutex.unlock();
					fileName = fileNames[0];
					qfileinfo = QFileInfo(fileName);
					continue;
				}
				else if(fileNames.count() > 0 && fileNames.count() < 2)
				{
					fileNames.removeAt(0);
					m_errUpLoad.append(m_notUpLoad.at(0));
					m_qmutex.lock();
					if (!m_notUpLoad.isEmpty())
					{
						m_notUpLoad.removeAt(0);
					}
					m_qmutex.unlock();
					ui.clientProgressBar->reset();
					qlistmodel->setStringList(m_notUpLoad);
					qlistmodelOk->setStringList(fileNamesOk);
					tcpSocket->abort();
					bytesWritten = 0;
					bytesToWrite = 0;
					TotalBytes = 0;
					blfileHeader = true;
					disconnect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
					disconnect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
					localFile->close();
					m_signalFileSize = 0;
					m_transferSpeed = 0;
					m_filesize = 0;
					ui.lbspeed->setText("0kb/s");  
					ui.lb1_2->setText("0");
					ui.lb1_4->setText("0");
					ui.lbtransfer->setText("传输完成" + QString::number(fileNamesOk.count()) + "个文件");
					blIsTransfer = false;
					return;
				}
				else
				{
					return;
				}
			}
		}
		else
		{return;}
		int n_num = 0;  //检测文件中断时间的判断次数
		localFile = new QFile(fileName);  
		while(!localFile->open(QFile::ReadOnly))  
		{  
			QFileInfo fileOrdir(fileName);
			if(!fileOrdir.exists())
			{
				disconnect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
				disconnect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
				tcpSocket->abort();
				return;
			}
			else
			{
				Sleep(1000);
				n_num++;
				if(!n_num < 30)
				{
					continue;
				}
				else
				{
					if(!fileNames.isEmpty())
					{
						fileNames.removeAt(0);
						m_errUpLoad.append(m_notUpLoad.at(0));
						m_qmutex.lock();
						if(!m_notUpLoad.isEmpty())
						{
							m_notUpLoad.removeAt(0);
						}
						m_qmutex.unlock();
					}
					if(!fileNames.count() > 0)
					{
						tcpSocket = new QTcpSocket();
						tcpSocket->connectToHost(QHostAddress(m_serverIp),m_serverPort);  
						connect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
						connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
						connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
							this,SLOT(displayError(QAbstractSocket::SocketError)));
					}
				}
			}
		}  
		TotalBytes = localFile->size(); 
		QDataStream sendOut(&outBlock,QIODevice::WriteOnly);  
		sendOut.setVersion(QDataStream::Qt_4_7);  
		QStringList currentFilelist = fileName.split(m_watchpath.replace('\\','/') + '/');
		QString currentFile = currentFilelist[1];
		clientMessage = "UP_FILE>";
		clientMessage += currentFile;
		clientMessage += "<UP_END";
		sendOut<<qint64(0)<<qint64(0)<<clientMessage;  //构造一个临时的文件头
		TotalBytes += outBlock.size();  //获得文件头的实际存储大小
		sendOut.device()->seek(0);  //将读写操作指向从头开始
		sendOut<<TotalBytes<<qint64(outBlock.size()- sizeof(qint64)*2);  
		bytesToWrite = TotalBytes - tcpSocket->write(outBlock);  
		//qDebug()<<clientMessage<<TotalBytes;  
		outBlock.resize(0); 
	}
	catch(QString err)
	{
		QMessageBox::information(this,"警告！","startTransfer err");
	}
}  

void CasitMedClient::updateClientProgress(qint64 numBytes)  
{  
	try
	{
		if(isDownFile)
		{
			return;
		}
		bytesWritten += (int)numBytes;  
		m_signalFileSize += (int)numBytes;
		emit speedsignal((int)numBytes);
		if(blfileHeader)
		{
			blfileHeader = false;
			m_signalFileSize -= (int)numBytes;
		}
		if(bytesToWrite > 0)  
		{  
			if(bytesToWrite > 0)  
			{  
				outBlock = localFile->read(qMin(bytesToWrite,loadSize));  
				bytesToWrite -= (int)tcpSocket->write(outBlock);  
				outBlock.resize(0);  
			}  
			else  
			{  
				localFile->close();  
			}  
		}  
		ui.clientProgressBar->setMaximum(m_filesize);  
		ui.clientProgressBar->setValue(m_signalFileSize);  
		int _speed = m_transferSpeed / 3096;
		if(_speed < 0.1)
		{
			ui.lbspeed->setText(QString::number(m_transferSpeed / 2048) + "B/s");
		}
		else if(_speed > 1024)
		{
			ui.lbspeed->setText(QString::number(m_transferSpeed / 4120) + "M/s");
		}
		else
		{
			ui.lbspeed->setText(QString::number(m_transferSpeed / 3096) + "K/s");  
		}
		qDebug()<<bytesWritten<<" "<<TotalBytes; 
		if(bytesWritten == TotalBytes)   //单个文件传输完毕
		{
			//fileInfotoXml(fileName,TotalBytes,"UpFile");
			//isOpenFile = true;
			//_transferdatastore->deletedatasqlite("upload_file",m_fileId);
			emit transferOksignal("deletefile");
			if(fileNames.count()>0)
			{
				fileNames.removeAt(0);
				m_qmutex.lock();
				if(!m_notUpLoad.isEmpty())
				{
					m_notUpLoad.removeAt(0);
				}
				m_qmutex.unlock();
			}
			bytesWritten = 0;
			bytesToWrite = 0;
			TotalBytes = 0;
			blfileHeader = true;
			disconnect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
			disconnect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
			localFile->close();
			fileNamesOk.append(fileName.right(fileName.size() - fileName.lastIndexOf('/')-1));
			fileName.clear();
			ui.lb1_4->setText(QString::number(fileNames.count()));
			qlistmodel->setStringList(m_notUpLoad);
			qlistmodelOk->setStringList(fileNamesOk);
			if(!fileNames.isEmpty())
			{
				
				isDownFile = false;
				ui.lb1_4->setText(QString::number(fileNames.count()));
				loadSize = 4*1024;  
				TotalBytes = 0;  
				bytesWritten = 0;  
				bytesToWrite = 0;
				tcpSocket->abort();
				Sleep(100);
				tcpSocket = new QTcpSocket();
				tcpSocket->connectToHost(QHostAddress(m_serverIp),m_serverPort);  
				connect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
				connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
				connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
					this,SLOT(displayError(QAbstractSocket::SocketError)));
			}
			else
			{
				tcpSocket->abort();
				m_signalFileSize = 0;
				m_transferSpeed = 0;
				m_filesize = 0;
				//ui.clientProgressBar->setMaximum(m_filesize);  
				//ui.clientProgressBar->setValue(m_signalFileSize);
				ui.clientProgressBar->reset();
				ui.lbspeed->setText("0kb/s");  
				ui.lb1_2->setText("0");
				m_filesize = 0;
				ui.lbtransfer->setText("传输完成 " + QString::number(fileNamesOk.count()) + "个文件");
				blIsTransfer = false;
				emit transferOksignal("ok");
			}
		}
	}
	catch (QString err)
	{
		QMessageBox::information(this,"警告！","updateClientProgress err");
	}
}  

void CasitMedClient::displayError(QAbstractSocket::SocketError socketError)  
{  
	if(socketError == QTcpSocket::RemoteHostClosedError)  
		return;  
	ui.clientProgressBar->reset();  
	ui.lbtransfer->setText("网络错误,正在尝试重连...");
	disconnect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
	disconnect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
	disconnect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
	this,SLOT(displayError(QAbstractSocket::SocketError)));
	tcpSocket->abort();  
	Sleep(500);
	if(blIsopenfile)
	{
		localFile->close();
	}
	//localFile->close();
	loadSize = 4*1024;  
	TotalBytes = 0;  
	bytesWritten = 0;  
	bytesToWrite = 0;
	tcpSocket = new QTcpSocket();
	tcpSocket->connectToHost(QHostAddress(m_serverIp),m_serverPort);  
	//tcpSocket->waitForConnected();
	connect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
	connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
	connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
		this,SLOT(displayError(QAbstractSocket::SocketError))); 
	//ui.lbtransfer->setText("连接成功");
} 

void CasitMedClient::downLoadFile()
{
	isDownFile = true;
	blockSize = 0;
	tcpSocket->abort();
	tcpSocket->connectToHost(m_serverIp,m_serverPort);
	
	QString sFile = fileName.right(fileName.size()-  
		fileName.lastIndexOf('/')-1);
	sFile = ui.leDownLoad->text();
	clientMessage = "DOWN_FILE>";
	clientMessage += sFile;
	clientMessage += "<DOWN_END";
	QByteArray block;
	QDataStream out(&block,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);
	out<<qint64(0)<<qint64(0)<<clientMessage;
	TotalBytes += block.size();
	out.device()->seek(0);
	out<<TotalBytes<<qint64(block.size() - sizeof(qint64)*2);
	tcpSocket->write(block);
	tcpSocket->waitForReadyRead(30000);
	disconnect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));  
	disconnect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
	connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(clientReceiveFile()));
}

void CasitMedClient::clientReceiveFile()
{
	QDataStream in(tcpSocket);  
	in.setVersion(QDataStream::Qt_4_7); 
	if(bytesReceived <= sizeof(qint64)*2)  
	{  
		if((tcpSocket->bytesAvailable() >=  
			sizeof(qint64)*2)&&(fileNameSize==0))  
		{  
			in>>TotalBytes>>fileNameSize;  
			bytesReceived += sizeof(qint64)*2;  
		}  
		if((tcpSocket->bytesAvailable()>=  
			fileNameSize)&&(fileName ==0))  
		{  
			in>>fileName;  
			QString sFile = fileName.left(fileName.indexOf('>') + 1);
			sFile += fileName.right(fileName.size()- fileName.lastIndexOf('<'));
			if(sFile == "DATA_BEGIN><DATA_END")
			{
				ui.lbtransfer->setText("no such file!");
				TotalBytes = 0;
				fileNameSize = 0;
				bytesReceived = 0;
				sFile.clear();
				fileName.clear();
				tcpSocket->abort();
				return;
			}
			bytesReceived += fileNameSize;  
			localFile = new QFile("D:\\FileLoadTest\\" + fileName);  //文件存储的路径
			if(!localFile->open(QFile::WriteOnly))  
			{  
				blIsopenfile = false;
				return;  
			}
			blIsopenfile = true;   //文件已经被打开
		}  
		else  
		{  
			return;  
		}  
	}  
	if(bytesReceived<TotalBytes)  
	{  
		bytesReceived += tcpSocket->bytesAvailable();  
		inBlock = tcpSocket->readAll();  
		localFile->write(inBlock);  
		inBlock.resize(0);  
	}   
	ui.clientProgressBar->setMaximum(TotalBytes);  
	ui.clientProgressBar->setValue(bytesReceived);  
	//ui.clientStatusLabel->setText(tr("Have sent %1KB").arg(bytesReceived/(1024))); 
	if(bytesReceived == TotalBytes)  
	{   
		localFile->close();
		fileInfotoXml(fileName,TotalBytes,"DownLoadFile");
		TotalBytes = 0;
		bytesReceived = 0;
		fileNameSize = 0;
		fileName.clear();
		tcpSocket->abort();
		delete localFile;
		QApplication::restoreOverrideCursor();  /*恢复为普通光标*/
	} 
}

void CasitMedClient::fileInfotoXml(QString filename,qint64 filesize, QString upordown)
	/*filename:文件名称；filesize：文件大小；upordown:上传还是下载*/
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
	QDomDocument document;
	QFile fileStory("Info.xml");
	if(!fileStory.exists("Info.xml"))
	{
		if(!fileStory.open(QIODevice::WriteOnly|QIODevice::Text))
		{
			return;
		}
		QString strHeader("version=\"1.0\" encoding=\"UTF-8\"");
		document.appendChild( document.createProcessingInstruction("xml", strHeader) );  

		QDomElement root_elem = document.createElement( "items" );   
		document.appendChild( root_elem );  
		QDomElement item1 = document.createElement( "item" );  
		item1.setAttribute( "filename", filename );  
		item1.setAttribute( "filesize", filesize );
		item1.setAttribute( "timer", current_date );  
		item1.setAttribute( "upordown", upordown );
		item1.setAttribute( "md5", dataChange->FileDigest(filename));
		root_elem.appendChild( item1 );  
		QTextStream out( &fileStory );  
		document.save( out, 4 );  
		fileStory.close(); 
	}
	else if(fileStory.exists("Info.xml"))
	{
		if(!fileStory.open(QIODevice::ReadOnly))
			{
				return;
			}
		if(!document.setContent(&fileStory,false))
		{
			fileStory.close();
			return;
		}
		fileStory.close();
		if(!fileStory.open(QIODevice::WriteOnly|QIODevice::Text))
		{
			return;
		}
		QDomElement roote = document.documentElement();
		QDomElement item_roote = roote.firstChildElement();
		QDomElement item1 = document.createElement( "item" );  
		item1.setAttribute( "filename", filename );  
		item1.setAttribute( "filesize", filesize );
		item1.setAttribute( "timer", current_date );  
		item1.setAttribute( "upordown", upordown );
		item1.setAttribute( "md5", dataChange->FileDigest(filename));
		item_roote.appendChild( item1 );
		QTextStream out( &fileStory );  
		document.save( out, 4 );  
		fileStory.close(); 
	}
}

void CasitMedClient::foldertoupdate(const QString &path)
{
	QDir *fDir = new QDir(path);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(fDir->entryInfoList());
	int j = fileInfo->count();
	int i;
	for(i = 0;i<fileInfo->count();i++)
	{
		if(fileInfo->at(i).fileName()=="."|fileInfo->at(i).fileName()=="..")
		{
			i++;
			continue;
		}
		if(fileInfo->at(i).isDir())
		{
			//tempFileNames.append(fileInfo->at(i).filePath());
			//QFile qfile = new QFile(fileInfo->at(i));
			folderAllsize += fileInfo->at(i).size();
			continue;
		}
		//fileNames.append(fileInfo->at(i).filePath());
		folderAllsize += fileInfo->at(i).size();
	}
	for(int j = 0;j < tempFileNames.count();j++)
	{
		QString tempFile = tempFileNames[j];
		tempFileNames.removeAt(j);
		findFiles(tempFile);
	}
}

void CasitMedClient::startProcess()
{
	pProcess = new QProcess();
	QString processPath = "mainFileWatch.exe";
	pProcess->start(processPath);
}

void CasitMedClient::closeEvent(QCloseEvent *event)
{
	//this->hide();
	//this->close();
	/*if(myTrayIcon->isVisible())
	{
	hide();
	event->ignore();
	}*/
}

void CasitMedClient::systemSet()
{
}

void CasitMedClient::mousePressEvent(QMouseEvent *event)
{  
	if(event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		move_point = event->pos();//鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
	}
}
void CasitMedClient::mouseMoveEvent(QMouseEvent *event)
{
	//鼠标左键被按下
	if(mouse_press)
	{
		QPoint move_pos = event->globalPos();//鼠标相对于屏幕的位置
		this->move(move_pos - move_point);//移动主窗体位置
	}
}

void CasitMedClient::mouseReleaseEvent(QMouseEvent *event)
{  
	mouse_press = false;//设置鼠标为未被按下
}

void CasitMedClient::creatTrayMenu()  
{  
	miniSizeAction = new QAction("Min(&N)",this);  
	maxSizeAction = new QAction("Max(&X)",this);  
	restoreWinAction = new QAction("Restore(&R)",this);  
	quitAction = new QAction("Quit(&Q)",this);  
	this->connect(miniSizeAction,SIGNAL(triggered()),this,SLOT(hide()));  
	this->connect(maxSizeAction,SIGNAL(triggered()),this,SLOT(showMaximized()));  
	this->connect(restoreWinAction,SIGNAL(triggered()),this,SLOT(showNormal()));  
	this->connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));  
	myMenu = new QMenu((QWidget*)QApplication::desktop());  
	myMenu->addAction(miniSizeAction);  
	myMenu->addAction(maxSizeAction);  
	myMenu->addAction(restoreWinAction);  
	myMenu->addSeparator();     //加入一个分离符  
	myMenu->addAction(quitAction);  
}  

void CasitMedClient::creatTrayIcon()
{
	creatTrayMenu();  
	if (!QSystemTrayIcon::isSystemTrayAvailable())      //判断系统是否支持系统托盘图标  
	{  
		return;  
	}  
	myTrayIcon = new QSystemTrayIcon(this);  
	myTrayIcon->setIcon(QIcon("VIRSIMlogo.ico"));   //设置图标图片  
	setWindowIcon(QIcon("VIRSIMlogo.ico"));  //把图片设置到窗口上  
	myTrayIcon->setToolTip("UpLoad V1.0");    //托盘时，鼠标放上去的提示信息  
	myTrayIcon->showMessage("Casit","Casit",QSystemTrayIcon::Information,10000);  
	myTrayIcon->setContextMenu(myMenu);     //设置托盘上下文菜单  
	myTrayIcon->show();  
	this->connect(myTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));  
}

void CasitMedClient::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch(reason)
	{
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:  
		showNormal(); 
		break; 
	case QSystemTrayIcon::MiddleClick:  
		myTrayIcon->showMessage("Casit","Casit",QSystemTrayIcon::Information,10000);  
		break;  
	default:  
		break;
	}
}

void CasitMedClient::minAction()
{
	showMinimized();
}

void CasitMedClient::showMinimized()
{
	if (myTrayIcon->isVisible())  
	{  
		myTrayIcon->showMessage("Casit","hide",QSystemTrayIcon::Information,5000);  
		hide();     //最小化  
		//event->ignore();  
	}  
	else  
	{
		//event->accept(); 
	}
}

void CasitMedClient::creatSystemSetIni()
{
	ui.pbSure->show();
	ui.leWatchPath->show();
	ui.pbWatchPath->show();
	if(dataChange->fileExist("Setting.ini"))
	{
		ui.leWatchPath->setText(dataChange->readINI(""));
	}
}

qint64 CasitMedClient::fileSize(QStringList _files)
{
	qint64 filesize = 0;
	foreach(QString str, _files)
	{
		QFileInfo fileinfo(str);
		if(fileinfo.isFile())
		{
			filesize += fileinfo.size();
		}
		else
		{
		}
	}
	return filesize;
}

CasitMedClient::~CasitMedClient()
{
	delete myTrayIcon;
}

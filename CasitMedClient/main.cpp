/************************************************************************/
/*                                 文件传输模块                         */
/************************************************************************/
//#include "casitmedclient.h"
#include "stdafx.h"
#include "mythread.h"
#include "DirectoryWatch.h"
#include "watchfilewatch.h"
#include "transferdatastore.h"
#include <QtGui/QApplication>
//#include <QTextCodec>

QStringList m_fileAbsulatePath;
QMutex qmutex;
QFileInfo m_qfileinfo;   //文件or目录
int m_fileNum = 0;
datachange *_datachange;
transferdatastore *_transferdatastore;
QString dir_s;
void NotifyAction(DWORD dwAction, LPWSTR szFile, DWORD dwLength)
{
	bool _blAddFile = false;
	bool _blChangeFile = false;
	switch(dwAction)
	{
	case FILE_ACTION_ADDED:
		//qDebug("FILE_ACTION_ADDED 添加: \t");
		_blAddFile = true;
		break;

	case FILE_ACTION_REMOVED:
		//qDebug("FILE_ACTION_REMOVED 删除: \n\t");
		break;

	case FILE_ACTION_MODIFIED:
		//qDebug("FILE_ACTION_MODIFIED 修改: \n\t");
		break;

	case FILE_ACTION_RENAMED_OLD_NAME:
		/*_blChangeFile = true;
		qDebug("FILE_ACTION_RENAMED_OLD_NAME 原文件名: \n\t");*/
		break;

	case FILE_ACTION_RENAMED_NEW_NAME:
		_blChangeFile = true;
		qDebug("FILE_ACTION_RENAMED_NEW_NAME 新的文件名: \n\t");
		break;

	default:
		break;
	}
	if(_blAddFile)
	{
		qmutex.lock();
		WCHAR szPath[MAX_PATH] = {0};   //文件相对路径
		wmemcpy(szPath, szFile, min(dwLength, MAX_PATH));
		//qDebug("%s %d", szPath, ++m_fileNum);
		QString str = QString::fromStdWString(szPath);
		QFileInfo m_qfileinfo(dir_s + '\\' + QString::fromStdWString(szPath));
		if(m_qfileinfo.isDir())
		{
			qmutex.unlock();
			return;
		}
		qDebug()<<str<<++m_fileNum;
		m_fileAbsulatePath.append(dir_s.replace('\\','/') + '/' + QString::fromStdWString(szPath).replace('\\','/'));
		qmutex.unlock();
	}
	if(_blChangeFile)
	{
		WCHAR szPath[MAX_PATH] = {0};   //文件相对路径
		wmemcpy(szPath, szFile, min(dwLength, MAX_PATH));
		QString str1 = QString::fromStdWString(szPath);
		qDebug()<<str1;
	}
}

void watchFileWatch::timerEvent(QTimerEvent *event)
{
	if(!m_fileAbsulatePath.isEmpty())
	{
		qmutex.lock();
		m_watchFile.append(m_fileAbsulatePath);
		qmutex.unlock();
		m_fileAbsulatePath.clear();
		/*foreach(QString str1,m_watchFile)
		{
		_transferdatastore->insertdatasqlite("upload_file","a/b/ce/d/d.txt",str1,5023);
		}*/
		emit sendsignal();
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QTextCodec::setCodecForTr((QTextCodec::codecForLocale()));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	QTextCodec *codec = QTextCodec::codecForName("System");  
	//QTextCodec *codec = QTextCodec::codecForName("GB2312");  
	QTextCodec::setCodecForLocale(codec);  
	QTextCodec::setCodecForCStrings(codec);  
	QTextCodec::setCodecForTr(codec); 
	//_transferdatastore = new transferdatastore(NULL);
	if(!_datachange->fileExist("Setting.ini"))
	{
		QDir qdir;
		if(!qdir.exists("C:\\FileLoad"))
		{
			if(!qdir.mkdir("C:\\FileLoad"))
			{
				return 0;
			}
		}
		_datachange->writeINI("C:\\FileLoad");
	}
	dir_s= _datachange->readINI("");
	if(dir_s.isEmpty())
	{
		_datachange->writeINI("C:\\FileLoad");
	}
	dir_s.replace('/','\\');
	TCHAR *_tchar = (wchar_t*) dir_s.utf16();
	CDirectoryWatch watch;
	qDebug("Start Directory Watch ...\n");
	watch.StartDirectoryWatch(_tchar, NotifyAction);

	watchFileWatch *m_watchfilewatch = new watchFileWatch();
	m_watchfilewatch->start();

	mythread *mythread1 = new mythread();
	mythread1->start();
	
	return a.exec();
}

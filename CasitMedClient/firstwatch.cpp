#include "firstwatch.h"

firstwatch::firstwatch()
	: QThread()
{
	qstringlist = findFiles(_datachange->readINI(""));
}

void firstwatch::run()
{
	exec();
}

QStringList firstwatch::findFiles(const QString &path)
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
		_qstringlist.append(fileInfo->at(i).filePath());
	}
	for(int j = 0;j < tempFileNames.count();j++)
	{
		QString tempFile = tempFileNames[j];
		tempFileNames.removeAt(j);
		findFiles(tempFile);
	}
	return _qstringlist;
}

QFileInfoList firstwatch::GetFileList(QString path)
{
	QDir dir(path);
	QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

	for(int i = 0; i != folder_list.size(); i++)
	{
		QString name = folder_list.at(i).absoluteFilePath();
		QFileInfoList child_file_list = GetFileList(name);
		file_list.append(child_file_list);
	}
	return file_list;
}

firstwatch::~firstwatch()
{

}

/************************************************************************/
/*                 文件传输模块                                                                     */
/************************************************************************/
#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QDialog>  
#include <QtNetwork/QAbstractSocket>  
//#include <QPushButton>  
//#include <QProgressBar>   
#include <QtNetwork/QTcpSocket>  
#include <QtNetwork/QHostAddress>  
//#include <QtGui/QDialogButtonBox>  
#include <QFile>  
#include <QString>  
#include <QByteArray>  
#include <QFileDialog>  
#include <QApplication>  
#include <QMessageBox>  
#include <QDebug>  
//#include <QHBoxLayout>  
//#include <QVBoxLayout> 
//#include <QThread>

class filetransfer : public QObject
{
	Q_OBJECT

public:
	void filetransferExternalInterface(QString _watchpath, QString _filename);

signals:
	/*错误信息*/
	void transferErrorSignal(QString _filename, int _fileid, QString errorinfo);
	/*传输过程中的信息*/
	void transferDataSignal(QString,QString,QString,QString,QString);
	/*传输完成后的信息*/
	void transferOkSignal();

public slots:
	/*开始传输*/
	void start();  
	void startTransfer();  
	void updateClientProgress(qint64 numBytes); 
	/*传输错误*/
	void displayError(QAbstractSocket::SocketError socketError);  

public:
	filetransfer(QObject *parent);
	~filetransfer();

private:
	QTcpSocket *tcpClient;  //
	bool isOpenFile;
	qint64 TotalBytes;  
	qint64 bytesWritten;  
	qint64 bytesToWrite;  
	qint64 loadSize;    //被初始化为一个4k的常量，尽可能将一个较大的文件分割，每次发送4kb大小
	QString m_fileName;  //文件绝对路径名称
	QFile *localFile;  
	QByteArray outBlock; 

	bool blIsopenfile;     //文件已被打开
	QString m_watchpath;   //文件监视路径
};

#endif // FILETRANSFER_H

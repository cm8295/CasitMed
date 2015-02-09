#ifndef CASITMEDCLIENT_H
#define CASITMEDCLIENT_H

#include <QtGui/QMainWindow>
#include "ui_casitmedclient.h"
#include "firstwatch.h"
#include "netwatch.h"
#include "transferdatastore.h"
#include <QDialog>  
#include <QNetworkInterface>
#include <QtNetwork>
#include <QtNetwork/QAbstractSocket>   
#include <QtNetwork/QTcpSocket>  
#include <QtNetwork/QHostAddress>  
#include <QtGui/QDialogButtonBox>  
#include <QtXml/QtXml>
#include <QFile>  
#include <QDir>
#include <QString>  
#include <QByteArray>  
#include <QFileDialog>  
#include <QApplication>  
#include <QMessageBox>  
#include <QDebug>  
#include <QThread>
#include <QtGui/QtGui>
#include <QFileDialog>
#include <qfiledialog.h>
#include <QMessageBox>
#include <Windows.h>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>

class CasitMedClient : public QMainWindow
{
	Q_OBJECT

public:
	/**************系统自带方法*******************************/
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);/*拖曳文件获取路径*/
	void closeEvent(QCloseEvent *event);/*系统关闭前触发的时间*/
	void showMinimized();
	void mousePressEvent(QMouseEvent *event);  //鼠标按下事件
	void mouseReleaseEvent(QMouseEvent *event);  //鼠标释放事件
	void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件

	/************************************************************************/
	/*                    自定义方法                                        */
	/************************************************************************/
	void fileInfotoXml(QString ,qint64 ,QString);   /*存储上传/下载的文件*/
	QStringList findFiles(const QString &path);     /*path为选择文件夹绝对路径*/
	void foldertoupdate(const QString &path);  /*检测文件夹是否有更新*/
	void transfer();
	void startProcess();
	void creatTrayMenu();     //创建托盘图标
	void creatTrayIcon();    //创建托盘图标ICON
	qint64 fileSize(QStringList _files);
	void systeminit();             //系统参数初始化
	void systemsignalslotinit();   //信号和槽初始化
	
signals:
	void speedsignal(int _speed);     //发送当前速度信号
	void transferOksignal(QString);   //一个文件传输完成后发送一个信号给线程，让线程来处理SQL语句，这样不会造成界面的卡顿现象

public slots:
	void start();  
	void startTransfer();  
	void updateClientProgress(qint64 numBytes);  
	void displayError(QAbstractSocket::SocketError socketError);  
	void openFile();             //打开文件 用于上传
	void downLoadFile();         //客户端下载文件
	void clientReceiveFile();   //客户端发送数据
	void transfererror();      //传输错误
	void connectClose();
	void systemSet();      //系统设置
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void minAction();   //最小化
	void creatSystemSetIni();//创建系统配置文件，修改监测路径
	void fileWatchPath();//修改文件监视路径
	void sureWatchPath();    //确定监视路径
	//

public:
	CasitMedClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CasitMedClient();
private:  
	//
	QList<QHostAddress> IPlist;
	QString clientMessage;
	QTcpSocket* tcpSocket;
	bool isOpenFile;
	qint64 TotalBytes;  
	qint64 bytesWritten;  
	qint64 bytesToWrite;  
	qint64 loadSize;    //被初始化为一个4k的常量，尽可能将一个较大的文件分割，每次发送4kb大小
	
	
	QStringList tempFileNames;
	QFile *localFile;  
	QByteArray outBlock; 
	qint16 blockSize;    //存放文件的大小信息
	QString message;   //存放从服务器接收到的字符串
	//
	qint64 bytesReceived;  //收到的总字节
	qint64 fileNameSize;  //准备读取的字节
	QByteArray inBlock;
	bool isDownFile;
	QString storyPath;    //存储文件路径，方便服务器建立文件夹路径
	QString m_serverIp;    //服务器Ip
	int m_serverPort;     //服务器端口
	QFileSystemWatcher m_filewatcher;  //监听文件变化
	int folderAllsize;
	QMutex m_qmutex;
	QProcess *pProcess;
	QStringList m_notUpLoad;   //正在上传的文件
	QStringList m_UpLoad;      //已经上传的文件
	QStringList m_errUpLoad;   //上传失败
	QStringListModel *qlistmodel;
	QStringListModel *qlistmodelOk;
	
	bool blfileHeader;     //是文件头
	bool blIsopenfile;

private:
	QPoint move_point; //移动的距离
	bool mouse_press; //鼠标按下
	
private: //最小化到托盘
	QSystemTrayIcon *myTrayIcon;  
	QMenu *myMenu;
	QAction *miniSizeAction;  
	QAction *maxSizeAction;  
	QAction *restoreWinAction; 
	QAction *quitAction;
public:
	QString m_watchpath;
	bool blIsTransfer;
	QStringList fileNames;   //存放所有文件列表
	QStringList fileNamesOk; //文件传输完毕后
	QStringList m_getOpenFileNames;  //获取对话框文件列表
	int m_transferSpeed;    //传输速度监测
	int m_fileId;              //存储数据库中文件ID
	QString fileName;    //
	QString m_filePathName;    //文件绝对路径
	qint64 m_filesize;    //文件总大小
	int m_signalFileSize;   //单个文件大小
private:
	Ui::CasitMedClientClass ui;
	datachange *dataChange;
	netwatch *_netwatch;
	firstwatch *_firstwatch;
	transferdatastore *_transferdatastore;
};

#endif // CASITMEDCLIENT_H

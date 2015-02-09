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
	/**************ϵͳ�Դ�����*******************************/
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);/*��ҷ�ļ���ȡ·��*/
	void closeEvent(QCloseEvent *event);/*ϵͳ�ر�ǰ������ʱ��*/
	void showMinimized();
	void mousePressEvent(QMouseEvent *event);  //��갴���¼�
	void mouseReleaseEvent(QMouseEvent *event);  //����ͷ��¼�
	void mouseMoveEvent(QMouseEvent *event);  //����ƶ��¼�

	/************************************************************************/
	/*                    �Զ��巽��                                        */
	/************************************************************************/
	void fileInfotoXml(QString ,qint64 ,QString);   /*�洢�ϴ�/���ص��ļ�*/
	QStringList findFiles(const QString &path);     /*pathΪѡ���ļ��о���·��*/
	void foldertoupdate(const QString &path);  /*����ļ����Ƿ��и���*/
	void transfer();
	void startProcess();
	void creatTrayMenu();     //��������ͼ��
	void creatTrayIcon();    //��������ͼ��ICON
	qint64 fileSize(QStringList _files);
	void systeminit();             //ϵͳ������ʼ��
	void systemsignalslotinit();   //�źźͲ۳�ʼ��
	
signals:
	void speedsignal(int _speed);     //���͵�ǰ�ٶ��ź�
	void transferOksignal(QString);   //һ���ļ�������ɺ���һ���źŸ��̣߳����߳�������SQL��䣬����������ɽ���Ŀ�������

public slots:
	void start();  
	void startTransfer();  
	void updateClientProgress(qint64 numBytes);  
	void displayError(QAbstractSocket::SocketError socketError);  
	void openFile();             //���ļ� �����ϴ�
	void downLoadFile();         //�ͻ��������ļ�
	void clientReceiveFile();   //�ͻ��˷�������
	void transfererror();      //�������
	void connectClose();
	void systemSet();      //ϵͳ����
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void minAction();   //��С��
	void creatSystemSetIni();//����ϵͳ�����ļ����޸ļ��·��
	void fileWatchPath();//�޸��ļ�����·��
	void sureWatchPath();    //ȷ������·��
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
	qint64 loadSize;    //����ʼ��Ϊһ��4k�ĳ����������ܽ�һ���ϴ���ļ��ָÿ�η���4kb��С
	
	
	QStringList tempFileNames;
	QFile *localFile;  
	QByteArray outBlock; 
	qint16 blockSize;    //����ļ��Ĵ�С��Ϣ
	QString message;   //��Ŵӷ��������յ����ַ���
	//
	qint64 bytesReceived;  //�յ������ֽ�
	qint64 fileNameSize;  //׼����ȡ���ֽ�
	QByteArray inBlock;
	bool isDownFile;
	QString storyPath;    //�洢�ļ�·������������������ļ���·��
	QString m_serverIp;    //������Ip
	int m_serverPort;     //�������˿�
	QFileSystemWatcher m_filewatcher;  //�����ļ��仯
	int folderAllsize;
	QMutex m_qmutex;
	QProcess *pProcess;
	QStringList m_notUpLoad;   //�����ϴ����ļ�
	QStringList m_UpLoad;      //�Ѿ��ϴ����ļ�
	QStringList m_errUpLoad;   //�ϴ�ʧ��
	QStringListModel *qlistmodel;
	QStringListModel *qlistmodelOk;
	
	bool blfileHeader;     //���ļ�ͷ
	bool blIsopenfile;

private:
	QPoint move_point; //�ƶ��ľ���
	bool mouse_press; //��갴��
	
private: //��С��������
	QSystemTrayIcon *myTrayIcon;  
	QMenu *myMenu;
	QAction *miniSizeAction;  
	QAction *maxSizeAction;  
	QAction *restoreWinAction; 
	QAction *quitAction;
public:
	QString m_watchpath;
	bool blIsTransfer;
	QStringList fileNames;   //��������ļ��б�
	QStringList fileNamesOk; //�ļ�������Ϻ�
	QStringList m_getOpenFileNames;  //��ȡ�Ի����ļ��б�
	int m_transferSpeed;    //�����ٶȼ��
	int m_fileId;              //�洢���ݿ����ļ�ID
	QString fileName;    //
	QString m_filePathName;    //�ļ�����·��
	qint64 m_filesize;    //�ļ��ܴ�С
	int m_signalFileSize;   //�����ļ���С
private:
	Ui::CasitMedClientClass ui;
	datachange *dataChange;
	netwatch *_netwatch;
	firstwatch *_firstwatch;
	transferdatastore *_transferdatastore;
};

#endif // CASITMEDCLIENT_H

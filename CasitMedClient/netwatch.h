/************************************************************************/
/*       网络连接监视模块                                               */
/************************************************************************/
#ifndef NETWATCH_H
#define NETWATCH_H

#include <QObject>
#include <QThread>
#include <Windows.h>
#include <QMessageBox>
#include <QNetworkConfigurationManager>
#include <QDebug>
#include <QNetworkInterface>
#include <QtNetwork>
#include <QtNetwork/QAbstractSocket>  
#include <QtNetwork/QTcpSocket> 
#include <QtNetwork/QHostAddress>  
#include <QTime>

class netwatch : public QThread
{
	Q_OBJECT

public:
	netwatch();
	~netwatch();
	void run();
public:
	QTcpSocket* m_pTcpSocket;  
	bool m_bServerConnected;  
	QTimer m_timer;  
	public slots:  
		void OnSocketError(QAbstractSocket::SocketError);  
		void OnSocketConnected();  
		void OnSocketDisconnected();  
		void ConnectServer();  
signals:  
		void ShowStatus(QString str);  

private:
	QNetworkConfigurationManager *_netwatch;
};

#endif // NETWATCH_H

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QObject>
#include <QtGui/QtGui>
#include <QtGui/QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <Windows.h>

class Parameters : public QObject
{
	Q_OBJECT

public:
	Parameters(QObject *parent);
	~Parameters();
	void CreatTrayMenu();
	void CreatTrayIcon();
	void closeEvent(QCloseEvent *event);
	private slots:
		void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
	QSystemTrayIcon *myTrayIcon;
	QMenu *myMenu;
	QAction *miniSizeAction;  
	QAction *maxSizeAction;  
	QAction *restoreWinAction; 
	QAction *quitAction;
};

#endif // PARAMETERS_H

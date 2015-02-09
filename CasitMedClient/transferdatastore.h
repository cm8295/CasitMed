#ifndef TRANSFERDATASTORE_H
#define TRANSFERDATASTORE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

class transferdatastore : public QObject
{
	Q_OBJECT

public:
	transferdatastore(QObject *parent);
	~transferdatastore();

public:
	bool createsqliteDB(QString sqlname);   //创建数据库
	bool createtablesqlite(QString tablename); //创建表
	bool createconnectsqlite(QString sqlname);   //连接数据库
	bool insertdatasqlite(QString tablename, QString _server_path, QString _local_path, int _file_size);   //插入数据
	bool deletedatasqlite(QString tablename, int _deletedata);   //删除数据
	bool updatadatasqlite(QString tablename, QString _updatadata);  //更新数据
	QStringList finddatasqlite(QString tablename);   //查询数据中文件的绝对路径和id序号，文件相对路径，文件绝对路径，文件大小
	bool insertAlldatasqlite(QString tablename, QStringList filedata);   //批量插入数据
	
	void createmysql(); //创建Mysql
	void createmysqlconnect();   //连接Mysql
	void filepathstorexml();     //存储文件路径等信息
public:
	QString sqliteName;
	QString fileinfostorename;
	QSqlDatabase db;
	QSqlQuery query;
};

#endif // TRANSFERDATASTORE_H

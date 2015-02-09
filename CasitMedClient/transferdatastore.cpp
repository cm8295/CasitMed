#include "transferdatastore.h"

transferdatastore::transferdatastore(QObject *parent)
	: QObject(parent)
{
	sqliteName = "CasitFileInformationStore.db";
}

bool transferdatastore::createconnectsqlite(QString sqlname)
{
	fileinfostorename = "CasitFileInformationStore.db";
	QFile _qfile(fileinfostorename);
	if(!_qfile.exists())
	{
		if(!createsqliteDB(fileinfostorename))
		{
			return false;
		}
		return true;
	}
	else
	{
		
		db = QSqlDatabase::addDatabase("QSQLITE"); 
		db.setDatabaseName(sqlname);
		if ( !db.open()){
			qDebug()<<"connect error";
			QMessageBox::critical(0,"cannot open database","unable to establish a database connection.",QMessageBox::Cancel);
			return false;
		}
		return true;
	}
}

bool transferdatastore::createsqliteDB(QString sqlname)
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(sqlname + ".db");
	db.setUserName("root");
	db.setPassword("123456");
	if ( !db.open()){
		qDebug()<<"create error";
		QMessageBox::critical(0,"cannot open database","unable to establish a database connection.",QMessageBox::Cancel);
		return false;
	}
	QSqlQuery query;
	bool success = query.exec("create table upload_file (task_id INTEGER NOT NULL PRIMARY KEY,server_path varchar(1024) COLLATE NOCASE, local_path varchar(1024) COLLATE NOCASE, status INTEGER,file_size INTEGER, isdir INTEGER,error_code INTEGER,add_time INTEGER,status_changetime INTEGER,  reserved1 INTEGER DEFAULT 0,reserved2 INTEGER DEFAULT 0,reserved3 TEXT DEFAULT '',reserved4 TEXT DEFAULT '' )");
	bool success1 = query.exec("create table upload_history_file (id INTEGER PRIMARY KEY,server_path varchar(1024) COLLATE NOCASE,  local_path varchar(1024) COLLATE NOCASE, isdir INTEGER,size INTEGER,op_starttime INTEGER,op_endtime INTEGER,  reserved1 INTEGER DEFAULT 0,reserved2 INTEGER DEFAULT 0,reserved3 TEXT DEFAULT '',reserved4 TEXT DEFAULT '',reserved5 TEXT DEFAULT '' )");
	bool success2 = query.exec("create table download_file (task_id INTEGER NOT NULL PRIMARY KEY,server_path varchar(1024) COLLATE NOCASE, local_path varchar(1024) COLLATE NOCASE, status INTEGER,file_size INTEGER,isdir INTEGER,error_code INTEGER, add_time INTEGER,status_changetime INTEGER,download_url TEXT,download_type INTEGER,  param1 TEXT,param2 TEXT,param3 TEXT,param4 TEXT,param5 TEXT, reserved1 INTEGER DEFAULT 0,reserved2 INTEGER DEFAULT 0,reserved3 TEXT DEFAULT '',reserved4 TEXT DEFAULT '' )");
	bool success3 = query.exec("create table download_history_file (id INTEGER PRIMARY KEY,server_path varchar(1024) COLLATE NOCASE,  local_path varchar(1024) COLLATE NOCASE, isdir INTEGER,size INTEGER,op_starttime INTEGER,op_endtime INTEGER,download_type INTEGER,  reserved1 INTEGER DEFAULT 0,reserved2 INTEGER DEFAULT 0,reserved3 TEXT DEFAULT '',reserved4 TEXT DEFAULT '',reserved5 TEXT DEFAULT '' )");
	bool success4 = query.exec("create table cache_file (id INTEGER PRIMARY KEY AUTOINCREMENT, server_path  varchar(1024) COLLATE NOCASE NOT NULL UNIQUE, fid  INTEGER, server_filename  varchar(1024), file_size INTEGER, md5  TEXT, block_list  TEXT, isdir  INTEGER, category  INTEGER, server_mtime  INTEGER, server_ctime INTEGER, local_mtime  INTEGER, local_ctime INTEGER,parent_path varchar(1024) COLLATE NOCASE,reserved1 TEXT DEFAULT '',reserved2 TEXT DEFAULT '',reserved3 INTEGER DEFAULT 0,reserved4 INTEGER DEFAULT 0)");
	bool success5 = query.exec("create table backup_file (local_filename varchar(1024) NOT NULL COLLATE NOCASE,  base_dir varchar(1024) NOT NULL COLLATE NOCASE,file_size INTEGER,mtime INTEGER,is_dir INTEGER, reserved1 INTEGER DEFAULT 0,reserved2 INTEGER DEFAULT 0,reserved3 TEXT DEFAULT '',reserved4 TEXT DEFAULT '',reserved5 TEXT DEFAULT '',reserved6 TEXT DEFAULT '',reserved7 TEXT DEFAULT '',CONSTRAINT pk_backupfile PRIMARY KEY(local_filename,base_dir) )");
	bool success6 = query.exec("create table version (table_name TEXT NOT NULL PRIMARY KEY,version INTEGER)");
	if(success){
		qDebug()<<QObject::tr("创建数据库成功！ \n");
		return true;
	}else{
		qDebug()<<QObject::tr("创建数据库失败！ \n");
		return false;
	}
}

bool transferdatastore::insertAlldatasqlite(QString tablename, QStringList filedata)
{
	//QString sql = "insert into " + tablename + "(server_path,local_path,file_size)" + " values("+ "'"  + "aaa" + "')";
	QString sql = "insert into upload_file (server_path, local_path) values('?', '?')";
	QSqlQuery query;
	query.prepare(sql);
	QVariantList local_path;
	local_path << "Tom" << "Jack" << "Jane" << "Jerry";
	query.addBindValue(local_path);
	/*QVariantList ages;
	ages << 20 << 23 << 22 << 25;
	query.addBindValue(ages);*/
	if (!query.execBatch()) 
	{
		/*QMessageBox::critical(0, QObject::tr("Database Error"),
			query.lastError().text());*/
		qDebug() << "error";
	}
	query.finish();
	query.exec("SELECT server_path, local_path FROM " + tablename);
	while (query.next()) 
	{
		QString name = query.value(0).toString();
		int age = query.value(1).toInt();
		qDebug() << name << ": " << age;
	}
	return true;
}

bool transferdatastore::insertdatasqlite(QString tablename, QString _server_path, QString _local_path, int _file_size)
{
	QSqlQuery query(db);
	QString sql = "insert into " + tablename + "(server_path,local_path,file_size)" + " values("+ "'"  + _server_path + "'"  + "," + "'"  + _local_path + "'"  + "," + "'"  + QString::number(_file_size) + "'"  + ")";
	if(!query.exec(sql))
	{
		return false;
	}
	return true;
}

bool transferdatastore::deletedatasqlite(QString tablename, int _deletedata)
{
	QSqlQuery query(db);
	QString str = "delete from " + tablename + " where task_id=" + "'" + QString::number(_deletedata) + "'";
	if(!query.exec(str))
	{
		return false;
	}
	return true;
}

QStringList transferdatastore::finddatasqlite(QString tablename)
{
	QStringList _fileinfo;
	QSqlQuery query(db);
	QString sql = "select task_id,server_path,local_path,file_size from " + tablename;
	if(!query.exec(sql))
	{
		return _fileinfo;
	}
	query.next();
	_fileinfo.append(query.value(0).toString());  //任务ID 唯一
	_fileinfo.append(query.value(1).toString());  //文件的相对路径
	_fileinfo.append(query.value(2).toString());  //文件的绝对路径
	_fileinfo.append(query.value(3).toString());  //文件大小
	return _fileinfo;
}

bool transferdatastore::updatadatasqlite(QString tablename, QString _updatadata)
{
	return true;
}

bool transferdatastore::createtablesqlite(QString tablename)
{
	return true;
}

void transferdatastore::createmysqlconnect()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // 使用mysql数据库驱动 
	db.setHostName("localhost");
	db.setDatabaseName("exampledb"); // 数据库名称
	db.setUserName("sa"); //  用户名
	db.setPassword("1"); // 密码
	bool ok = db.open(); // 尝试连接数据库
	if(ok)
	{
	}
}

transferdatastore::~transferdatastore()
{

}

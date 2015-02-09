#ifndef FILEWATCH_H
#define FILEWATCH_H

#include <QObject>

class filewatch : public QObject
{
	Q_OBJECT

public:
	filewatch(QObject *parent);
	~filewatch();

private:
	
};

#endif // FILEWATCH_H

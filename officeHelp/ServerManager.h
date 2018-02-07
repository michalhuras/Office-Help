#ifndef SERVERMENAGER_H
#define SERVERMENAGER_H

#include <QObject>
#include <QString>


class ServerManager :public QObject {
	Q_OBJECT

protected:
	QString mPath;
	QString mTextToSearch;

public:
	ServerManager();
	QString getPath();
	QString getTextToSearch();

public slots:
	void setPath(QString aPath);
	void setTextToSearch(QString aTextToSearch);


};

#endif // SERVERMENAGER_H

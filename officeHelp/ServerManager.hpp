#ifndef SERVERMENAGER_H
#define SERVERMENAGER_H

#include <QObject>
#include <QString>

#include <datastructevidence.hpp>

class ServerManager :public QObject {
	Q_OBJECT

public:
	ServerManager();
	QString getPath();
	QString getTextToSearch();
	CUS::searchMode getSearchMode();

public slots:
	void setPath(QString aPath);
	void setTextToSearch(QString aTextToSearch);
	void setSearchMode(CUS::searchMode aSearchMode);

protected:
	QString mPath;
	QString mTextToSearch;
	CUS::searchMode mSearchMode;
};

#endif // SERVERMENAGER_H

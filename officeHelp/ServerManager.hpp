#ifndef SERVERMENAGER_H
#define SERVERMENAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <datastructevidence.hpp>

class ServerManager :public QObject {
	Q_OBJECT

public:
	ServerManager();
	QString getPath();
	QString getTextToSearch();
	CUS::searchMode getSearchMode();
	QStringList getFilesInDirectory();
	QStringList getFilesInDirectoryRecursively();
	QVector<CUS::searchReult> getSearchResultInFile();


public slots:
	void setPath(QString aPath);
	void setTextToSearch(QString aTextToSearch);
	void setSearchMode(CUS::searchMode aSearchMode);
	void setfilesInDirectory(QStringList filesInDirectory);
	void setfilesInDirectoryRecursively(QStringList filesInDirectoryRecursively);
	void setFilesAndResultsInDirectory(QVector<CUS::searchReult> SearchResultInFile);


protected:
	QString mPath;
	QString mTextToSearch;
	CUS::searchMode mSearchMode;
	QStringList mFilesInDirectory;
	QStringList mFilesInDirectoryRecursively;
	QVector<CUS::searchReult> mSearchResultInFile;
};

#endif // SERVERMENAGER_H

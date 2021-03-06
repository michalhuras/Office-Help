#ifndef SERVERMENAGER_H
#define SERVERMENAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QList>

#include <datastructevidence.hpp>

class ModelManager :public QObject {
	Q_OBJECT

public:
	ModelManager();
	QString getPath();
	QString getTextToSearch();
	CUS::searchMode getSearchMode();
	QStringList getFilesInDirectory();
	QStringList getFilesInDirectoryRecursively();
	QList<QTreeWidgetItem *> getSearchResultInFile();
	QList<QTreeWidgetItem *> getFilesInDirectoryRecursivelyToView();
	void setfilesInDirectoryRecursively(QStringList filesInDirectoryRecursively);


public slots:
	void setPath(QString aPath);
	void setTextToSearch(QString aTextToSearch);
	void setSearchMode(CUS::searchMode aSearchMode);
	void setfilesInDirectory(QStringList filesInDirectory);
	void setFilesAndResultsInDirectory(QList<QTreeWidgetItem *> SearchResultInFile);


protected:
	QString mPath;
	QString mTextToSearch;
	CUS::searchMode mSearchMode;
	QStringList mFilesInDirectory;
	QStringList mFilesInDirectoryRecursively;
	QList<QTreeWidgetItem *> mSearchResultInFile;
	QList<QTreeWidgetItem *> mFilesInDirectoryRecursivelyView;
};

#endif // SERVERMENAGER_H

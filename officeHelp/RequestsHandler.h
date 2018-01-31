#ifndef REUESTSHANDLER_H
#define REUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QDebug>

class RequestsHandler
{
public:
	enum searchMode {
		error = -1,
		inThisCatalog = 0,
		inThisCatalogRecursevely = 1,
		inThisFile = 2};

private:
	QVector<QString> listOfFiles;
	QString catalogPath;
	QString wordToSearch;
	searchMode choosenSearchMode;
   // jakoś trzeba wcisnąć obserwatorów

	RequestsHandler();
	void createFileList();
};

#endif // REUESTSHANDLER_H

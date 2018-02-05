#ifndef REUESTSHANDLER_H
#define REUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <boost\Signals.hpp>

class RequestsHandler
{
public:
	enum searchMode {
		error = -1,
		inThisCatalog = 0,
		inThisCatalogRecursevely = 1,
		inThisFile = 2};

public:
	void catalogPathChangeSlot();
	void wordToSearchChangeSlot();


private:
	QVector<QString> listOfFiles;
	QString catalogPath;
	QString wordToSearch;
	searchMode choosenSearchMode;


	RequestsHandler();
	void createFileList();
	void setCatalogPath();
	void setWordToSearch();



};

#endif // REUESTSHANDLER_H

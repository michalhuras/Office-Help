#ifndef REUESTSHANDLER_H
#define REUESTSHANDLER_H

#define <QVector>
#define <QString>

class RequestsHandler
{

private:
	QVector<QString> listOfFiles;
	QString catalogPath;
	Qstring wordToSearch;
	searchMode choosenSearchMode;
public:
	enum searchMode {
		error = -1,
		inThisCatalog = 0,
		inThisCatalogRecursevely = 1,
		inThisFile = 2};

	RequestsHandler();
	void createFileList();
};

#endif // REUESTSHANDLER_H

#ifndef REUESTSHANDLER_H
#define REUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <QObject>

class RequestsHandler :public QObject {
	Q_OBJECT

public:
	RequestsHandler();
	enum searchMode {
		error = -1,
		inThisCatalog = 0,
		inThisCatalogRecursevely = 1,
		inThisFile = 2};

public slots:
	void catalogPathChangeSlot(QString newValue);
	void wordToSearchChangeSlot(QString newValue);


private:
	QVector<QString> listOfFiles;
	QString catalogPath;
	QString wordToSearch;
	searchMode choosenSearchMode;

	void createFileList();
	void setCatalogPath();
	void setWordToSearch();



};

#endif // REUESTSHANDLER_H

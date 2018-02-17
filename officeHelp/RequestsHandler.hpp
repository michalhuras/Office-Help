#ifndef REUESTSHANDLER_H
#define REUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QDebug> // TO DO
#include <QObject>
#include <QPair>
#include <QVariant>

#include <datastructevidence.hpp>
#include <ServerManager.hpp>

class RequestsHandler :public QObject {
	Q_OBJECT

public:
	RequestsHandler(ServerManager *aServerManager);

signals:
	void showSearchInFileResults(QVector <QPair<QVariant, QString> >);
	void showFilesInDirectory(QStringList);

public slots:
	void catalogPathChangeSlot(QString newValue);
	void wordToSearchChangeSlot(QString newValue);
	void searchButtonClicked();
	void showFilesInDirectoryButtonClicked();


private:
	ServerManager *mServerManager;

	void searchInFile();
	QVector <QPair<QVariant, QString> > readFileLines();



	//QVector<QString> listOfFiles;
	//QString catalogPath;
	//QString wordToSearch;
	//void createFileList();
	//void setCatalogPath();
	//void setWordToSearch();
	//void searchingInFile();



};

#endif // REUESTSHANDLER_H

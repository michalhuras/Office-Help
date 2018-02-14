#ifndef REUESTSHANDLER_H
#define REUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <QObject>

#include <datastructevidence.hpp>
#include <ServerManager.hpp>

class RequestsHandler :public QObject {
	Q_OBJECT

public:
	RequestsHandler(ServerManager *aServerManager);

public slots:
	void catalogPathChangeSlot(QString newValue);
	void wordToSearchChangeSlot(QString newValue);
	void searchButtonClicked();


private:
	void searchInFile();
	ServerManager *mServerManager;

	//QVector<QString> listOfFiles;
	//QString catalogPath;
	//QString wordToSearch;

	//void createFileList();
	//void setCatalogPath();
	//void setWordToSearch();
	//void searchingInFile();



};

#endif // REUESTSHANDLER_H

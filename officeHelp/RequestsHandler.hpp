#ifndef REQUESTSHANDLER_H
#define REQUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QStringList>
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
	void displaySearchInFileResults(QVector <QPair<QVariant, QString> >);
	void displayFilesInDirectory(QStringList);
	void displayFilesInDirectoryRecursively(QStringList);
	void displayFilesAndResultsInDirectory(QVector<CUS::searchReult>);

public slots:
	void catalogPathChangeSlot(QString newValue);
	void wordToSearchChangeSlot(QString newValue);
	void searchButtonClicked();
	void showFilesInDirectoryButtonClicked();
	void showFilesInDirectoryRecursivelyButtonClicked(); // TO DO -za długa nazwa
	void searchInListedFilesButton2Clicked();

private:
	ServerManager *mServerManager;

	void searchInFile();
	QVector <QPair<QVariant, QString> > readFileLines();
	void createFileListRecursively(QString CatalogPath, QStringList *mList, QString prefix = "");

};

#endif // REQUESTSHANDLER_H

//TO DO -usunąć zbędne komentarze z plików cpp

#ifndef REQUESTSHANDLER_H
#define REQUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug> // TODO
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
	void displayFilesAndResultsInDirectory(QList<QTreeWidgetItem *>);

public slots:
	void catalogPathChangeSlot(QString newValue);
	void wordToSearchChangeSlot(QString newValue);
	void searchButtonClicked();
	void showFilesInDirectoryButtonClicked();
	void showFilesInDirectoryRecursivelyButtonClicked(); // TODO -za długa nazwa
	void searchInListedFilesButton2Clicked();

private:
	ServerManager *mServerManager;

	void searchInFile();
	QVector <QPair<QVariant, QString> > readFileLines();
	void createFileListRecursively(
			QString CatalogPath,
			QStringList *mList,
			QString prefix = "",
			bool recursively = false);
	QList<QTreeWidgetItem *> createQTreeWidgetItemList(
			QString catalogPath,
			QStringList *filesList,
			QString searchedText);
};

#endif // REQUESTSHANDLER_H

//TO DO -usunąć zbędne komentarze z plików cpp

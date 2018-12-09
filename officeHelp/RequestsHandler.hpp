#ifndef REQUESTSHANDLER_H
#define REQUESTSHANDLER_H

#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QObject>
#include <QPair>
#include <QVariant>

#include <datastructevidence.hpp>
#include <ModelManager.hpp>

class RequestsHandler :public QObject {
	Q_OBJECT

public:
	RequestsHandler(ModelManager *aServerManager);
	QStringList GetListOfFilesInDirectory();
	QList<QTreeWidgetItem *> SearchInFiles(QStringList FilesList);
	void UpdateFilesInDirectoryRecursively();
	QStringList createFileListRecursively(
			QString CatalogPath,
			QString prefix = "",
			bool recursively = false);
	void UpdateSearchInAllFilesRecursively();

signals:
	void displaySearchInFileResults(QVector <QPair<QVariant, QString> >);
	void displayFilesInDirectory(QStringList);
	void displayFilesInDirectoryRecursively(QStringList);
	void displayFilesAndResultsInDirectory(QList<QTreeWidgetItem *>);

public slots:
	void catalogPathChangeSlot(QString newValue);
	void wordToSearchChangeSlot(QString newValue);
	void searchButtonClicked();

private:
	ModelManager *mServerManager;

	void searchInFile();
	QVector <QPair<QVariant, QString> > readFileLines();

	QList<QTreeWidgetItem *> createQTreeWidgetItemList(
			QString catalogPath,
			QStringList filesList,
			QString searchedText);
};

#endif // REQUESTSHANDLER_H

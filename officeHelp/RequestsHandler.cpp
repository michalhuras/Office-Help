#include "RequestsHandler.hpp"

#include <QFile>
#include <QDir>
#include <QVector>
#include <QString>
#include <QFileInfo>
#include <QStandardItem>

#include <QDebug>

RequestsHandler::RequestsHandler(ModelManager *aServerManager):
		mServerManager(aServerManager) {;}

void RequestsHandler::catalogPathChangeSlot(QString newValue) {
	qDebug() << "catalog path changed:  " << newValue;
}

void RequestsHandler::wordToSearchChangeSlot(QString newValue) {
	qDebug() << "word to search changed:  " << newValue;
}

void RequestsHandler::searchButtonClicked() {
searchInFile();
}

QStringList RequestsHandler::showFilesInDirectory() {
	QString catalogPath = mServerManager->getPath();
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();
	QDir pathDir = QDir(catalogPath);
	QStringList filesList;
	filesList = pathDir.entryList(QStringList("*"),
								  QDir::Files | QDir::NoSymLinks,
								  QDir::Name);
	return filesList;
}

void RequestsHandler::showFilesInDirectoryRecursivelyButtonClicked() { //TO Do za długa nazwa
	QString catalogPath = mServerManager->getPath();
	QStringList filesList;
	QStringList *mFilesList = &filesList;

	//Check if path is to file or Catalog
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();

	//Create file list recursively
	createFileListRecursively(catalogPath, mFilesList, "", true);
	emit displayFilesInDirectoryRecursively(filesList);
	//TO DO czy to jest najlepsza opcja przekazywania -wskaźnik
}

void RequestsHandler::searchInListedFilesButton2Clicked() {
	QString catalogPath = mServerManager->getPath();
	QStringList *filesList = new QStringList;

	//Check if path is to file or Catalog
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();

	//Create file list
	createFileListRecursively(catalogPath, filesList, "", true);

	QList<QTreeWidgetItem *> items = createQTreeWidgetItemList(
										catalogPath,
										filesList,
										mServerManager->getTextToSearch());

	emit displayFilesAndResultsInDirectory(items);
}

void RequestsHandler::searchInFile() {
	QVector <QPair<QVariant, QString> > vRetrievalResult = readFileLines();

	int foundLines = 0;
	while(foundLines != vRetrievalResult.size()) {
		if ( vRetrievalResult.at(foundLines).second.contains(
				 mServerManager->getTextToSearch(), Qt::CaseInsensitive))
			foundLines++;
		else
			vRetrievalResult.erase(vRetrievalResult.begin() + foundLines);
	}

	emit displaySearchInFileResults(vRetrievalResult);
}

QVector <QPair<QVariant, QString> > RequestsHandler::readFileLines() {
	QVector <QPair<QVariant, QString> > vRetrievalResult;

	QFile file(mServerManager->getPath());
	qDebug() << mServerManager->getPath();

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		file.close();
		return vRetrievalResult;
	}

	//Read lines from file and save to QVector
	int lineNumber = 0;
	QTextStream in(&file);
	while (!in.atEnd()) {
		lineNumber++;
		QString lineText = in.readLine();
		qDebug() << lineText;
		vRetrievalResult.push_back(QPair<QVariant , QString >(lineNumber,lineText));
	}
	return vRetrievalResult;
}

void RequestsHandler::createFileListRecursively(QString path,
												QStringList *mList,
												QString prefix,
												bool recursively) {

	QDir dirForFiles = QDir(path);
	QStringList filesList;
	filesList = dirForFiles.entryList(QStringList("*"), QDir::Files | QDir::NoSymLinks,
									  QDir::Name);

	QString fileToAdd;
	while (!filesList.isEmpty()) {
		if (prefix == "")
			fileToAdd = prefix;
		else
			fileToAdd = prefix + "/";
		mList->append(prefix + filesList.first());
		filesList.erase(filesList.begin());
	}

	QDir dirForCatalogs = QDir(path);
	QStringList catalogList;
	catalogList = dirForCatalogs.entryList(QStringList("*"),
										   QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

	while (!catalogList.isEmpty()) {
		if (recursively)
			createFileListRecursively(
						path + "/" + catalogList.first(),
						mList,
						prefix + "/" + catalogList.first(),
						true);
		catalogList.erase(catalogList.begin());
	}
}

QList<QTreeWidgetItem *> RequestsHandler::createQTreeWidgetItemList(
		QString catalogPath,
		QStringList *filesList,
		QString searchedText){

	QList<QTreeWidgetItem *> items;
	int fileNumber = 1;
	int numberOfFiles = filesList->size();
	while(!filesList->isEmpty()) {
		QTreeWidgetItem *nextFile = new QTreeWidgetItem();
		if ((numberOfFiles > 99 && fileNumber > 99) ||
			(numberOfFiles <100 &&  numberOfFiles > 9 &&
			 fileNumber < 100  && fileNumber > 9)) {
			nextFile->setText(0, QString::number(fileNumber));
		}
		else if (numberOfFiles < 100 && numberOfFiles > 9 &&
				 fileNumber <= 9) {
			nextFile->setText(0, "0" + QString::number(fileNumber));
		}
		else if ((numberOfFiles > 99 && fileNumber < 99) ) {
			nextFile->setText(0, "00" + QString::number(fileNumber));
		}
		else {
			nextFile->setText(0, QString::number(fileNumber));
		}
		nextFile->setText(1, filesList->first());

		QStringList vRetrievalResult;
		QFile file(catalogPath + "/" + filesList->at(0));
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			//Read lines from file and save to QStringlist
			QTextStream in(&file);
			while (!in.atEnd()) {
				QString lineText = in.readLine();
				vRetrievalResult << lineText;
			}
		}

		QList<QTreeWidgetItem *> nextRow;
		//Process received data
		int lineNumber = 0;
		while(lineNumber < vRetrievalResult.size()) {
			if ( vRetrievalResult.at(lineNumber).contains(
					 searchedText, Qt::CaseInsensitive)) {
				if ((lineNumber <= vRetrievalResult.size() -2) && (lineNumber >= 3)) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;
					for (int i = lineNumber - 2; i <= lineNumber + 2; i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
				}
				else if ((lineNumber <3) && (vRetrievalResult.size() <= 4)) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;

					for (int i = 0; i < vRetrievalResult.size(); i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
				}
				else if ((lineNumber <=3) && (lineNumber < vRetrievalResult.size() - 2)) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;
					for (int i = 0; i <= lineNumber + 2; i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
				}
				else if (lineNumber > vRetrievalResult.size() - 2) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;

					for (int i = lineNumber - 2; i < vRetrievalResult.size(); i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
				}
				else {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;
					QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
					tempItem2->setText(3,vRetrievalResult.at(lineNumber));
				}
			}
		lineNumber++;
		}

		// adding a row to an item starts a subtree
		nextFile->insertChildren(1, nextRow);
		items.append(nextFile);
		filesList->removeFirst();
		fileNumber++;
	}

	return items;
}

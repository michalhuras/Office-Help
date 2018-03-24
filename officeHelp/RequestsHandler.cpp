#include "RequestsHandler.hpp"

#include <QFile>
#include <QDir>
#include <QVector>
#include <QString>
#include <QFileInfo>
#include <QStandardItem>

RequestsHandler::RequestsHandler(ServerManager *aServerManager):
		mServerManager(aServerManager) {;}
//SLOTS
void RequestsHandler::catalogPathChangeSlot(QString newValue) {
	qDebug() << "catalog path changed:  " << newValue;
}

void RequestsHandler::wordToSearchChangeSlot(QString newValue) {
	qDebug() << "word to search changed:  " << newValue;
}

void RequestsHandler::searchButtonClicked() {
	switch (mServerManager->getSearchMode()) {
	case CUS::error:
		break;
	case CUS::inThisCatalog:
		break;
	case CUS::inThisCatalogRecursevely:
		break;
	case CUS::inThisFile:
		searchInFile();
		break;
	default:
		break;
	}
}

void RequestsHandler::showFilesInDirectoryButtonClicked() {
	QString catalogPath = mServerManager->getPath();

	//Check if path is to file or Catalog
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();

	//Create file list
	QDir pathDir = QDir(catalogPath);
	QStringList filesList;
	filesList = pathDir.entryList(QStringList("*"),
								  QDir::Files | QDir::NoSymLinks,
								  QDir::Name);
	//TODO wyeksportować to do osobnej funkcji żeby można było to wykorzystać w innych metodach

	emit displayFilesInDirectory(filesList);
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

//PRIVATE FUNCTIONS
void RequestsHandler::searchInFile() {
	QVector <QPair<QVariant, QString> > vRetrievalResult = readFileLines();

	//Process received data
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

	//Open file
	QFile file(mServerManager->getPath());
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
		vRetrievalResult.push_back(QPair<QVariant , QString >(lineNumber,lineText));
	}
	return vRetrievalResult;
}

void RequestsHandler::createFileListRecursively(QString path,   //blabla bla
												QStringList *mList,
												QString prefix,
												bool recursively) {
//TO DO nazewnictowo -ujednolicić przedrostki (mList)

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
	int fileNumber = 0;
	while(!filesList->isEmpty()) {
		QTreeWidgetItem *nextFile = new QTreeWidgetItem();
		nextFile->setText(0, QString::number(fileNumber));
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
				if ((lineNumber < 2) && (5 > vRetrievalResult.size())) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					//tempItem1->setText(0, "");
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;

					for (int i = 0; i < vRetrievalResult.size(); i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
					//results.push_back(vRetrievalResult.mid(0,vRetrievalResult.size()));
				}
				else if (lineNumber < 2) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;

					for (int i = 0; i < vRetrievalResult.size() + 3; i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
					//results.push_back(vRetrievalResult.mid(0,vRetrievalResult.size() + 3));
					//TODO trzeba to popoprawiać
				}
				else if (lineNumber + 2 > vRetrievalResult.size()) {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;

					for (int i = lineNumber - 2; i < vRetrievalResult.size() - lineNumber; i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
					//results.push_back(vRetrievalResult.mid(lineNumber - 2, vRetrievalResult.size() - lineNumber ));
				}
				else {
					QTreeWidgetItem *tempItem1 = new QTreeWidgetItem();
					tempItem1->setText(2, vRetrievalResult.at(lineNumber));
					nextRow << tempItem1;

					for (int i = lineNumber - 2; i < 5; i++) {
						QTreeWidgetItem *tempItem2 = new QTreeWidgetItem(tempItem1);
						tempItem2->setText(3,vRetrievalResult.at(i));
					}
					//results.push_back(vRetrievalResult.mid(lineNumber - 2, 5));
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

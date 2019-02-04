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

QStringList RequestsHandler::GetListOfFilesInDirectory() {
	QString catalogPath = mServerManager->getPath();
	catalogPath += "/";
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();
	QDir pathDir = QDir(catalogPath);
	QStringList filesList;
	filesList = pathDir.entryList(QStringList("*"),
								  QDir::Files | QDir::NoSymLinks,
								  QDir::Name);
	return filesList;
}

void RequestsHandler::UpdateFilesInDirectoryRecursively(){
	QString catalogPath = mServerManager->getPath();
	QStringList filesList;

	//Check if path is to file or Catalog
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();

	//Create file list recursively
	filesList = createFileListRecursively(catalogPath,"", true);
	mServerManager->setfilesInDirectoryRecursively(filesList);
}

void RequestsHandler::UpdateSearchInAllFilesRecursively() {
	QString catalogPath = mServerManager->getPath();
	QStringList filesList;

	//Check if path is to file or Catalog
	QFileInfo fileInformations(catalogPath);
	catalogPath = fileInformations.path();

	//Create file list
	filesList = createFileListRecursively(catalogPath, "", true);

	QList<QTreeWidgetItem *> items = createQTreeWidgetItemList(
										catalogPath,
										filesList,
										mServerManager->getTextToSearch());
	mServerManager->setFilesAndResultsInDirectory(items);
}

QList<QTreeWidgetItem *> RequestsHandler::SearchInFiles(QStringList FilesList) {
	QString catalogPath = mServerManager->getPath();
	qDebug() <<"FilesList  " << FilesList;

	return createQTreeWidgetItemList(catalogPath,
									 FilesList,
									 mServerManager->getTextToSearch());

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

QStringList RequestsHandler::createFileListRecursively(
		QString path,
		QString prefix,
		bool recursively) {
	qDebug() << "createFileListRecursively  ";
	qDebug() << "path "  << path;
	qDebug() << "prefix "  << prefix;
	qDebug() << "recursively "  << recursively;

	QStringList mList;
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
		mList.append(prefix + filesList.first());
		filesList.erase(filesList.begin());
	}

	QDir dirForCatalogs = QDir(path);
	QStringList catalogList;
	catalogList = dirForCatalogs.entryList(QStringList("*"),
										   QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

	while (!catalogList.isEmpty()) {
		if (recursively)
			mList += createFileListRecursively(
						path + "/" + catalogList.first(),
						prefix + "/" + catalogList.first(),
						true);
		catalogList.erase(catalogList.begin());
	}

	return mList;
}


QList<QTreeWidgetItem *> RequestsHandler::createQTreeWidgetItemList(
		QString catalogPath,
		QStringList filesList,
		QString searchedText){

	qDebug() << "createQTreeWidgetItemList  ";
	qDebug() << "catalogPath "  << catalogPath;
	qDebug() << "filesList "  << filesList;
	qDebug() << "searchedText "  << searchedText;
	QList<QTreeWidgetItem *> items;
	int fileNumber = 1;
	int numberOfFiles = filesList.size();
	while(!filesList.isEmpty()) {
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
		nextFile->setText(1, filesList.first());

		QStringList vRetrievalResult;
		QFile file(catalogPath + "/" + filesList.at(0));
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
		filesList.removeFirst();
		fileNumber++;
	}
	return items;
}

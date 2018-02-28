#include "RequestsHandler.hpp"

#include <QFile>
#include <QDir>
#include <QVector>
#include <QString>
#include <QFileInfo>


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
	createFileListRecursively(catalogPath, mFilesList,"");
	emit displayFilesInDirectoryRecursively(filesList);
	//TO DO czy to jest najlepsza opcja przekazywania -wskaźnik
}

void RequestsHandler::searchInListedFilesButton2Clicked() {
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
	//TODO wyeksportować to do osobnej funkcji żeby można było to wykorzystać w innych
	//metodach

	QVector<CUS::searchReult> result;
	while(!filesList.isEmpty()) {
		//TODO wyeksportować to do osobnej funkcji

		CUS::searchReult newResult;
		newResult.fileDirectory = catalogPath + filesList.at(0);
		newResult.fileName = filesList.at(0);

		QVector <QPair<int, QString> > vRetrievalResult;
		QFile file(catalogPath + filesList.at(0));
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			//Read lines from file and save to QVector
			int lineNumber = 0;
			QTextStream in(&file);
			while (!in.atEnd()) {
				lineNumber++;
				QString lineText = in.readLine();
				vRetrievalResult.push_back(QPair<int , QString >(lineNumber,lineText));
			}
		}

		QVector<QVector<QPair<int , QString > > > results;
		//Process received data
		int lineNumber = 0;
		while(lineNumber != vRetrievalResult.size()) {
		if ( vRetrievalResult.at(lineNumber).second.contains(
					 mServerManager->getTextToSearch(), Qt::CaseInsensitive)) {
				if ((lineNumber < 2) && (5 > vRetrievalResult.size())) {
					results.push_back(vRetrievalResult.mid(0,vRetrievalResult.size()));
				}
				else if (lineNumber < 2) {
					results.push_back(vRetrievalResult.mid(0,vRetrievalResult.size() + 3));
				}
				else if (lineNumber + 2 > vRetrievalResult.size()) {
					results.push_back(vRetrievalResult.mid(lineNumber - 2, vRetrievalResult.size() - lineNumber ));
				}
				else {
					results.push_back(vRetrievalResult.mid(lineNumber - 2, 5));
				}
		}
		lineNumber++;
		}

		newResult.results = results;
		newResult.numberOfResults= results.count();
		result.append(newResult);
	}

	emit displayFilesAndResultsInDirectory(result);
}

//void RequestsHandler::() {
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

void RequestsHandler::createFileListRecursively(QString path,
												QStringList *mList,
												QString prefix)
{ //TO DO nazewnictowo -ujednolicić przedrostki (mList)


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
		createFileListRecursively(path + "/" + catalogList.first(), mList,
								  prefix + "/" + catalogList.first());
		catalogList.erase(catalogList.begin());
	}
}

/*
CUS::searchReult *RequestsHandler::createSearchResults() {



}

*/




#include "RequestsHandler.hpp"

#include <QFile>
#include <QDir>
#include <QVector>
#include <QString>

RequestsHandler::RequestsHandler(ServerManager *aServerManager):
		mServerManager(aServerManager) {;}

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
	//Check if path is to file
	//QFile file(mServerManager->getPath());
	//if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	//	return vRetrievalResult;

	//Create file list
	QDir pathDir = QDir(mServerManager->getPath());
	QStringList filesList;
	filesList = pathDir.entryList(QStringList("*"), QDir::Files | QDir::NoSymLinks);
	emit showFilesInDirectory(filesList);
}

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

	emit showSearchInFileResults(vRetrievalResult);
}

QVector <QPair<QVariant, QString> > RequestsHandler::readFileLines() {
	QVector <QPair<QVariant, QString> > vRetrievalResult;

	//Open file
	QFile file(mServerManager->getPath());
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return vRetrievalResult;

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




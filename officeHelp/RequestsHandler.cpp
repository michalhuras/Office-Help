#include "RequestsHandler.hpp"

#include <QFile>
#include <QVector>

RequestsHandler::RequestsHandler(ServerManager *aServerManager):
		mServerManager(aServerManager) {;}

void RequestsHandler::catalogPathChangeSlot(QString newValue) {
	qDebug() << "catalog path changed:  " << newValue;
}

void RequestsHandler::wordToSearchChangeSlot(QString newValue) {
	qDebug() << "word to search changed:  " << newValue;
}

void RequestsHandler::searchButtonClicked() {
	qDebug() << "0. Jestem tu";

	switch (mServerManager->getSearchMode()) {
	case CUS::error:
		break;
	case CUS::inThisCatalog:
		break;
	case CUS::inThisCatalogRecursevely:
		break;
	case CUS::inThisFile:
		qDebug() << "1. Jestem tu";
		searchInFile();
		break;
	default:
		break;
	}
}

void RequestsHandler::searchInFile() {
	//I dont know if export it to other class
	//open file

	QFile file(mServerManager->getPath());
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	struct retrievalResult{
		int line;
		QString lineText;
	};

	QVector <retrievalResult> vRetrievalResult;

	int lineNumber = 0;

	QTextStream in(&file);
	while (!in.atEnd()) {
		lineNumber++;
		QString line = in.readLine();
		if (line.contains(mServerManager->getTextToSearch(), Qt::CaseInsensitive))
			vRetrievalResult.push_back(retrievalResult(lineNumber,line));
	}

	while(!vRetrievalResult.isEmpty()) {
		qDebug << vRetrievalResult.at(0).lineText;
		vRetrievalResult.erase(vRetrievalResult.begin());
	}

}



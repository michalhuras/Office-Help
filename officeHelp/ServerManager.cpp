#include "ServerManager.hpp"

#include <QDebug>

ServerManager::ServerManager() :
		mPath("C:/"),
		mTextToSearch(""),
		mSearchMode(CUS::inThisFile) {
}

QString ServerManager::getPath() {
	return mPath;
}

QString ServerManager::getTextToSearch() {
	return mTextToSearch;
}

CUS::searchMode ServerManager::getSearchMode() {
	return mSearchMode;
}

QStringList ServerManager::getFilesInDirectory() {
	return mFilesInDirectory;
}

QStringList ServerManager::getFilesInDirectoryRecursively() {
	return mFilesInDirectoryRecursively;
}

QList<QTreeWidgetItem *> ServerManager::getSearchResultInFile() {
	return mSearchResultInFile;
}

QList<QTreeWidgetItem *> ServerManager::getFilesInDirectoryRecursivelyToView() {
	return mFilesInDirectoryRecursivelyView;
}

void ServerManager::setPath(QString aPath) {
	if (mPath != aPath)
		mPath = aPath;
}

void ServerManager::setTextToSearch(QString aTextToSearch) {
	if (mTextToSearch != aTextToSearch)
		mTextToSearch = aTextToSearch;
}

void ServerManager::setSearchMode(CUS::searchMode aSearchMode) {
	if (aSearchMode != mSearchMode)
		mSearchMode = aSearchMode;
}

void ServerManager::setfilesInDirectory(QStringList filesInDirectory) {
	mFilesInDirectory = filesInDirectory;
}

void ServerManager::setfilesInDirectoryRecursively(QStringList filesInDirectoryRecursively) {
	mFilesInDirectoryRecursively = filesInDirectoryRecursively;

	QList<QTreeWidgetItem *> items;
	int fileNumber = 0;
	int numberOfFiles = filesInDirectoryRecursively.size();
	while (!filesInDirectoryRecursively.isEmpty()) {
		QTreeWidgetItem *temp = new QTreeWidgetItem();
		if ((numberOfFiles > 99 && fileNumber > 99) ||
			(numberOfFiles <100 &&  numberOfFiles > 9 &&
			 fileNumber < 100  && fileNumber > 9)) {
			temp->setText(0, QString::number(fileNumber));
		}
		else if (numberOfFiles < 100 && numberOfFiles > 9 &&
				 fileNumber <= 9) {
			temp->setText(0, "0" + QString::number(fileNumber));
		}
		else if ((numberOfFiles > 99 && fileNumber < 99) ) {
			temp->setText(0, "00" + QString::number(fileNumber));
		}
		else {
			temp->setText(0, QString::number(fileNumber));
		}
		temp->setText(1, filesInDirectoryRecursively.first());
		items.append(temp);
		filesInDirectoryRecursively.removeFirst();
		fileNumber++;
	}

	mFilesInDirectoryRecursivelyView = items;
}


void ServerManager::setFilesAndResultsInDirectory(QList<QTreeWidgetItem *> SearchResultInFile) {
	mSearchResultInFile = SearchResultInFile;
}

// TO DO:
// Dopisać do sygnałów i slotów testy jednostkowe`

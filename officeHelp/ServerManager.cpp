#include "ServerManager.hpp"

#include <QDebug>

ServerManager::ServerManager() :
		mPath("C:/TestingCatalog/DokumentTekstowy1.txt"),
		mTextToSearch("ala"),
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
	while (!filesInDirectoryRecursively.isEmpty()) {
		QTreeWidgetItem *temp = new QTreeWidgetItem();
		temp->setText(0, QString::number(fileNumber));
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

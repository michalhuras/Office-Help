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

QVector<CUS::searchReult> ServerManager::getSearchResultInFile() {
	return mSearchResultInFile;
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
}


void ServerManager::setFilesAndResultsInDirectory(QVector<CUS::searchReult> SearchResultInFile) {
	mSearchResultInFile = SearchResultInFile;
}


// TO DO:
// Dopisać do sygnałów i slotów testy jednostkowe
// czas realizacji: do 24.02.218

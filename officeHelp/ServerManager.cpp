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

void ServerManager::setPath(QString aPath) {
	if (mPath != aPath)
		mPath = aPath;
}

void ServerManager::setTextToSearch(QString aTextToSearch){
	if (mTextToSearch != aTextToSearch)
		mTextToSearch = aTextToSearch;
}

void ServerManager::setSearchMode(CUS::searchMode aSearchMode){
	if (aSearchMode != mSearchMode)
		mSearchMode = aSearchMode;
}


// TO DO:
// Dopisać do sygnałów i slotów testy jednostkowe
// czas realizacji: do 24.02.218

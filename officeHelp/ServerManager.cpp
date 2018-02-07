#include "ServerManager.h"



ServerManager::ServerManager() :
		mPath("C:/Users/Public/KatalogTestowy"),
		mTextToSearch("ala") {
}

QString ServerManager::getPath() {
	return mPath;
}

QString ServerManager::getTextToSearch() {
	return mTextToSearch;
}

void ServerManager::setPath(QString aPath) {
	mPath = aPath;
}

void ServerManager::setTextToSearch(QString aTextToSearch){
	mTextToSearch = aTextToSearch;
}

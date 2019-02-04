#include "ModelManager.hpp"

ModelManager::ModelManager() :
		mPath("C:/"),
		mTextToSearch(""),
		mSearchMode(CUS::inThisFile) {
}

QString ModelManager::getPath() {
	return mPath;
}

QString ModelManager::getTextToSearch() {
	return mTextToSearch;
}

CUS::searchMode ModelManager::getSearchMode() {
	return mSearchMode;
}

QStringList ModelManager::getFilesInDirectory() {
	return mFilesInDirectory;
}

QStringList ModelManager::getFilesInDirectoryRecursively() {
	return mFilesInDirectoryRecursively;
}

QList<QTreeWidgetItem *> ModelManager::getSearchResultInFile() {
	return mSearchResultInFile;
}

QList<QTreeWidgetItem *> ModelManager::getFilesInDirectoryRecursivelyToView() {
	return mFilesInDirectoryRecursivelyView;
}

void ModelManager::setPath(QString aPath) {
	if (mPath != aPath)
		mPath = aPath;
}

void ModelManager::setTextToSearch(QString aTextToSearch) {
	if (mTextToSearch != aTextToSearch)
		mTextToSearch = aTextToSearch;
}

void ModelManager::setSearchMode(CUS::searchMode aSearchMode) {
	if (aSearchMode != mSearchMode)
		mSearchMode = aSearchMode;
}

void ModelManager::setfilesInDirectory(QStringList filesInDirectory) {
	mFilesInDirectory = filesInDirectory;
}

void ModelManager::setfilesInDirectoryRecursively(QStringList filesInDirectoryRecursively) {
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


void ModelManager::setFilesAndResultsInDirectory(QList<QTreeWidgetItem *> SearchResultInFile) {
	mSearchResultInFile = SearchResultInFile;
}

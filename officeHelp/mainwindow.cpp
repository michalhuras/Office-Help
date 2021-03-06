#include <QFileDialog>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "ui_MainWindow.h"
#include "ui_FileDialog.hpp"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow),
	  mServerManager(new ModelManager),
	  mRequestsHandler(new RequestsHandler(mServerManager)) {
	ui->setupUi(this);

	setTablesStartingParameters();
	setSignalsAndSlotsConnections();

	ui->pathBox->setText(mServerManager->getPath());
	ui->textToFindBox->setText(mServerManager->getTextToSearch());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::setTablesStartingParameters(){
	QStringList labelsList1 = (QStringList() << "Line \nnumber" << "Line text");

	QStringList labels =
			(QStringList() << "Number" << "File name" << "Results" << "Expanded results");

	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setRowCount(1);
	ui->tableWidget->setColumnWidth(0,69);
	ui->tableWidget->setColumnWidth(1,500);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setHorizontalHeaderLabels(labelsList1);
	/*
	ui->treeWidget_2->setColumnCount(4);
	ui->treeWidget_2->setHeaderLabels(labels);
	ui->treeWidget_2->resizeColumnToContents(0);
	ui->treeWidget_2->resizeColumnToContents(1);
	ui->treeWidget_2->resizeColumnToContents(2);
	ui->treeWidget_2->resizeColumnToContents(3);
	*/
	ui->treeWidget_3->setColumnCount(4);
	ui->treeWidget_3->setHeaderLabels(labels);
	ui->treeWidget_3->resizeColumnToContents(0);
	ui->treeWidget_3->resizeColumnToContents(1);
	ui->treeWidget_3->resizeColumnToContents(2);
	ui->treeWidget_3->resizeColumnToContents(3);
}

void MainWindow::setSignalsAndSlotsConnections() {
	//mServerManager
	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					 mServerManager, SLOT(setPath(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					 mServerManager, SLOT(setTextToSearch(QString)));
	QObject::connect(this, SIGNAL(button1Clicked(CUS::searchMode)),
					 mServerManager, SLOT(setSearchMode(CUS::searchMode)));
	QObject::connect(this, SIGNAL(button2Clicked(CUS::searchMode)),
					 mServerManager, SLOT(setSearchMode(CUS::searchMode)));
	QObject::connect(this, SIGNAL(button3Clicked(CUS::searchMode)),
					 mServerManager, SLOT(setSearchMode(CUS::searchMode)));

	//mRequestsHandler
	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					 mRequestsHandler, SLOT(catalogPathChangeSlot(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					 mRequestsHandler, SLOT(wordToSearchChangeSlot(QString)));
	QObject::connect(this, SIGNAL(searchButtonClicked()),
					 mRequestsHandler, SLOT(searchButtonClicked()));
	//QObject::connect(this, SIGNAL(searchInListedFilesButton2Clicked()),
	//				 mRequestsHandler, SLOT(searchInListedFilesButton2Clicked()));
	QObject::connect(mRequestsHandler, SIGNAL( displaySearchInFileResults(QVector <QPair<QVariant, QString> >)),
					 this, SLOT(displaySearchInFileResults( QVector <QPair<QVariant, QString> >)));
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesAndResultsInDirectory(QList<QTreeWidgetItem *>)),
					 this, SLOT(displayFilesAndResultsInDirectory()));
}

void MainWindow::displaySearchInFileResults(QVector <QPair<QVariant, QString> > searchResults) {
	ui->tableWidget->setRowCount(searchResults.size());
	int rowNumber = 0;
	while (!searchResults.isEmpty()){
		ui->tableWidget->setItem(rowNumber,0,new QTableWidgetItem(
									 searchResults.begin()->first.toString()));
		ui->tableWidget->setItem(rowNumber,1,new QTableWidgetItem(
									 searchResults.begin()->second));
		rowNumber++;
		searchResults.erase(searchResults.begin());
	}
}

void MainWindow::displayFilesAndResultsInDirectory() {
	while (ui->treeWidget_3->topLevelItemCount())
		ui->treeWidget_3->takeTopLevelItem(0);
	ui->treeWidget_3->setColumnCount(4);
	QStringList labels =
			(QStringList() << "Number" << "File name" << "Results" << "Expanded results");
	ui->treeWidget_3->setHeaderLabels(labels);
	ui->treeWidget_3->insertTopLevelItems(
			0,
			mServerManager->getSearchResultInFile());
	ui->treeWidget_3->setSortingEnabled(true);
	ui->treeWidget_3->sortByColumn(0 ,Qt::AscendingOrder);
	ui->treeWidget_3->expandAll();
	ui->treeWidget_3->resizeColumnToContents(0);
	ui->treeWidget_3->resizeColumnToContents(1);
	ui->treeWidget_3->resizeColumnToContents(2);
	ui->treeWidget_3->resizeColumnToContents(3);
	ui->treeWidget_3->collapseAll();
}

void MainWindow::pathChanged(QString newPath, QString newName) {
	QString path = newPath;
	if (newName != "")
		path += "/" + newName;
	ui->pathBox->setText(path);
	emit onPathBoxEditingFinishedSignal(path);
}

void MainWindow::on_pathBox_editingFinished() {
	emit onPathBoxEditingFinishedSignal(ui->pathBox->text());
}

void MainWindow::on_textToFindBox_editingFinished() {
	emit onTextToFindBoxEditingFinishedSignal(ui->textToFindBox->text());
}

void MainWindow::on_pushButton_4_clicked()
{
	FileDialog aFileDialog;
	aFileDialog.setModal(true);
	QObject::connect(&aFileDialog, SIGNAL(newPathaccepted(QString, QString)),
					 this, SLOT(pathChanged(QString, QString)));
	aFileDialog.exec();
}

void MainWindow::on_pushButton_7_clicked()
{
	emit searchButtonClicked();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	switch (index) {
	case 0:
		emit button1Clicked(CUS::inThisFile);
		break;
	case 1:
		emit button1Clicked(CUS::inThisCatalog);
		break;
	case 2:
		emit button1Clicked(CUS::inThisCatalogRecursevely);
		break;
	default:
		break;
	}
}

void MainWindow::on_pushButton_5_clicked()
{
	// Show files in directory
	while (ui->treeWidget_2->topLevelItemCount())
		ui->treeWidget_2->takeTopLevelItem(0);
	QStringList filesList = mRequestsHandler->GetListOfFilesInDirectory();
	ui->treeWidget_2->setColumnCount(1);
	ui->treeWidget_2->setHeaderLabel("File");
	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < filesList.size(); i++)
		items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(filesList.at(i))));
	ui->treeWidget_2->insertTopLevelItems(0, items);
}

void MainWindow::on_pushButton_6_clicked()
{
	// Show files in directory recursively
	mRequestsHandler->UpdateFilesInDirectoryRecursively();
	QStringList labels = (QStringList() << "Number" << "File name");
	while (ui->treeWidget_3->topLevelItemCount())
		ui->treeWidget_3->takeTopLevelItem(0);
	ui->treeWidget_3->setColumnCount(2);
	ui->treeWidget_3->setHeaderLabels(labels);
	ui->treeWidget_3->resizeColumnToContents(0);
	ui->treeWidget_3->resizeColumnToContents(1);
	ui->treeWidget_3->insertTopLevelItems(
				0,
				mServerManager->getFilesInDirectoryRecursivelyToView());
	ui->treeWidget_3->setSortingEnabled(true);
	ui->treeWidget_3->sortByColumn(0 ,Qt::AscendingOrder);
}

void MainWindow::on_pushButton_8_clicked()
{
	// Search in listed files
	QStringList FilesList = mRequestsHandler->GetListOfFilesInDirectory();
	QList<QTreeWidgetItem *> item =
			mRequestsHandler->SearchInFiles(FilesList);
	while (ui->treeWidget_2->topLevelItemCount())
		ui->treeWidget_2->takeTopLevelItem(0);
	ui->treeWidget_2->setColumnCount(4);
	QStringList labels =
			(QStringList() << "Number" << "File name" << "Results" << "Expanded results");
	ui->treeWidget_2->setHeaderLabels(labels);
	ui->treeWidget_2->insertTopLevelItems(0, item);
	ui->treeWidget_2->setSortingEnabled(true);
	ui->treeWidget_2->sortByColumn(0 ,Qt::AscendingOrder);
	ui->treeWidget_2->expandAll();
	ui->treeWidget_2->resizeColumnToContents(0);
	ui->treeWidget_2->resizeColumnToContents(1);
	ui->treeWidget_2->resizeColumnToContents(2);
	ui->treeWidget_2->resizeColumnToContents(3);
	ui->treeWidget_2->collapseAll();
}

void MainWindow::on_pushButton_10_clicked()
{
	// Search in listed files
	mRequestsHandler->UpdateSearchInAllFilesRecursively();
	while (ui->treeWidget_3->topLevelItemCount())
		ui->treeWidget_3->takeTopLevelItem(0);
	ui->treeWidget_3->setColumnCount(4);
	QStringList labels =
			(QStringList() << "Number" << "File name" << "Results" << "Expanded results");
	ui->treeWidget_3->setHeaderLabels(labels);
	ui->treeWidget_3->insertTopLevelItems(
			0,
			mServerManager->getSearchResultInFile());
	ui->treeWidget_3->setSortingEnabled(true);
	ui->treeWidget_3->sortByColumn(0 ,Qt::AscendingOrder);
	ui->treeWidget_3->expandAll();
	ui->treeWidget_3->resizeColumnToContents(0);
	ui->treeWidget_3->resizeColumnToContents(1);
	ui->treeWidget_3->resizeColumnToContents(2);
	ui->treeWidget_3->resizeColumnToContents(3);
	ui->treeWidget_3->collapseAll();
}

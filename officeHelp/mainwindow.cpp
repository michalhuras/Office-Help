#include <QFileDialog>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow),
	  mServerManager(new ServerManager),
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
	QStringList labelsList1;
	labelsList1.append("Line \nnumber");
	labelsList1.append("Line text");

	QStringList labelsList2;
	labelsList2.append("Number");
	labelsList2.append("File\nname");
	labelsList2.append("Number\nof resuts");
	labelsList2.append("Text");

	ui->tableWidget->setColumnCount(4);
	ui->tableWidget->setRowCount(1);
	ui->tableWidget->setColumnWidth(0,69);
	ui->tableWidget->setColumnWidth(1,500);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setHorizontalHeaderLabels(labelsList1);

	ui->tableWidget_2->setColumnCount(4);
	ui->tableWidget_2->setRowCount(1);
	ui->tableWidget_2->setColumnWidth(0,69);
	ui->tableWidget_2->setColumnWidth(1,131);
	ui->tableWidget_2->setColumnWidth(2,69);
	ui->tableWidget_2->setColumnWidth(3,300);
	ui->tableWidget_2->verticalHeader()->setVisible(false);
	ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget_2->setHorizontalHeaderLabels(labelsList2);

	ui->tableWidget_3->setColumnCount(4);
	ui->tableWidget_3->setRowCount(1);
	ui->tableWidget_3->setColumnWidth(0,69);
	ui->tableWidget_3->setColumnWidth(1,131);
	ui->tableWidget_3->setColumnWidth(2,69);
	ui->tableWidget_3->setColumnWidth(3,300);
	ui->tableWidget_3->verticalHeader()->setVisible(false);
	ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setSignalsAndSlotsConnections() {
	//TO DO styl łamania jeden ustalić i ujednolić

	//mServerManager - mRequestsHandler
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesInDirectory(QStringList)),
					 mServerManager, SLOT(setfilesInDirectory(QStringList)));
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesInDirectoryRecursively(QStringList)),
					 mServerManager, SLOT(setfilesInDirectoryRecursively(QStringList)));
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesAndResultsInDirectory(QVector<CUS::searchReult>)),
					 mServerManager, SLOT(setFilesAndResultsInDirectory(QVector<CUS::searchReult>)));

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
	QObject::connect(this, SIGNAL(showFilesInDirectoryButtonClicked()),
					 mRequestsHandler, SLOT(showFilesInDirectoryButtonClicked()));
	QObject::connect(this, SIGNAL(showFilesInDirectoryRecursivelyButtonClicked()),
					 mRequestsHandler, SLOT( showFilesInDirectoryRecursivelyButtonClicked()));
	QObject::connect(this, SIGNAL(searchInListedFilesButton2Clicked()),
					 mRequestsHandler, SLOT(searchInListedFilesButton2Clicked()));
	QObject::connect(mRequestsHandler, SIGNAL( displaySearchInFileResults(QVector <QPair<QVariant, QString> >)),
					 this, SLOT(displaySearchInFileResults( QVector <QPair<QVariant, QString> >)));
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesInDirectory(QStringList)),
					 this, SLOT(displayFilesInDirectory()));
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesInDirectoryRecursively(QStringList)),
					 this, SLOT(displayFilesInDirectoryRecursively()));
	QObject::connect(mRequestsHandler, SIGNAL(displayFilesAndResultsInDirectory(QVector<CUS::searchReult>)),
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

void MainWindow::displayFilesInDirectory() {
	QStringList filesList = mServerManager->getFilesInDirectory();
	ui->tableWidget_2->setRowCount(filesList.size());
	QVariant rowNumber = 0;
	while (!filesList.isEmpty()){
		ui->tableWidget_2->setItem(rowNumber.toInt(),0,new QTableWidgetItem(
									   rowNumber.toString()));
		ui->tableWidget_2->setItem(rowNumber.toInt(),1,new QTableWidgetItem(
									   filesList.first()));
		rowNumber = rowNumber.toInt() + 1;
		filesList.erase(filesList.begin());
	}
}

void MainWindow::displayFilesInDirectoryRecursively(){
	QStringList tempFilesList = mServerManager->getFilesInDirectoryRecursively();
	QStringList *mFilesList = &tempFilesList;
	ui->tableWidget_3->setRowCount(mFilesList->size());
	QVariant rowNumber = 0;
	while (!mFilesList->isEmpty()){
		ui->tableWidget_3->setItem(rowNumber.toInt(),0,new QTableWidgetItem(
									   rowNumber.toString()));
		ui->tableWidget_3->setItem(rowNumber.toInt(),1,new QTableWidgetItem(
									   mFilesList->first()));
		rowNumber = rowNumber.toInt() + 1;
		mFilesList->erase(mFilesList->begin());
	}
}

void MainWindow::displayFilesAndResultsInDirectory() {

qDebug() << "Jestem tu... ";

}

void MainWindow::on_pathBox_editingFinished() {
	emit onPathBoxEditingFinishedSignal(ui->pathBox->text());
}

void MainWindow::on_textToFindBox_editingFinished() {
	emit onTextToFindBoxEditingFinishedSignal(ui->textToFindBox->text());
}

//Pomysł -> w trakcie działania programu można ustawiać te bozy na "setreadonly" żeby nie
// było jakiś problemów

void MainWindow::on_pushButton_4_clicked()
{
	//TO DO !!! ŻEBY MOŻNA BYŁO SOBIE WYBIERAĆ INTERESUJĄCE NAS PLIKI
	QFileDialog dialog(this);
	//dialog.setFileMode(QFileDialog::Directory );
	dialog.setOption(QFileDialog::ShowDirsOnly,false);
	QStringList filters;
	//filters << "Image files (*.png *.xpm *.jpg)"
	//		<< "Text files (*.txt)"
	//		<< "Any files (*)";
	//dialog.setNameFilters(filters);
	dialog.setFilter(QDir::AllDirs | QDir::Files);
	//dialog.setFileMode(QFileDialog::ExistingFile );
	dialog.setDirectory("C:/TestingCatalog/");
	dialog.setViewMode(QFileDialog::Detail);
	dialog.exec();
	QDir fileNames = dialog.directory();
	qDebug() << fileNames.absolutePath() << "    " << fileNames.dirName();

	//C:\TestingCatalog
	//QString fileName = QFileDialog::getOpenFileName(this,
	//	tr("Open file"), "C:/Users/Public", tr("Image Files (*.png *.jpg *.bmp *.txt)"));
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

void MainWindow::on_pushButton_3_clicked()
{
	//TO DO
	//When clicked it will export results and all setings
	//Creates .txt file, firstly saves settings from servermanager class, than results
}

void MainWindow::on_pushButton_5_clicked()
{
	emit showFilesInDirectoryButtonClicked();
}

void MainWindow::on_pushButton_6_clicked()
{
	emit showFilesInDirectoryRecursivelyButtonClicked();
}

void MainWindow::on_pushButton_8_clicked()
{
	emit searchInListedFilesButton1Clicked();
}

void MainWindow::on_pushButton_10_clicked()
{
	emit searchInListedFilesButton2Clicked();
}

void MainWindow::on_pushButton_2_clicked()
{

}

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

	QStringList labelsList1;
	labelsList1.append("Line \nnumber");
	labelsList1.append("Line text");

	QStringList labelsList2;
	labelsList2.append("# Number");
	labelsList2.append("File name");

	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setRowCount(1);
	ui->tableWidget->setColumnWidth(0,69);
	ui->tableWidget->setColumnWidth(1,500);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setHorizontalHeaderLabels(labelsList1);

	ui->tableWidget_2->setColumnCount(2);
	ui->tableWidget_2->setRowCount(1);
	ui->tableWidget_2->setColumnWidth(0,69);
	ui->tableWidget_2->setColumnWidth(1,500);
	ui->tableWidget_2->verticalHeader()->setVisible(false);
	ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget_2->setHorizontalHeaderLabels(labelsList2);


	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(catalogPathChangeSlot(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(wordToSearchChangeSlot(QString)));
	QObject::connect(this, SIGNAL(searchButtonClicked()),
					  mRequestsHandler, SLOT(searchButtonClicked()));
	QObject::connect(this, SIGNAL(showFilesInDirectoryButtonClicked()),
					  mRequestsHandler, SLOT(showFilesInDirectoryButtonClicked()));
	QObject::connect(mRequestsHandler, SIGNAL(
						 showSearchInFileResults(QVector <QPair<QVariant, QString> >)),
					 this, SLOT(showSearchInFileResults(
									QVector <QPair<QVariant, QString> >)));
	QObject::connect(mRequestsHandler, SIGNAL(showFilesInDirectory(QStringList)),
					 this, SLOT(showFilesInDirectory(QStringList)));
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

	ui->pathBox->setText(mServerManager->getPath());
	ui->textToFindBox->setText(mServerManager->getTextToSearch());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::showSearchInFileResults(QVector <QPair<QVariant, QString> > searchResults) {
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

void MainWindow::showFilesInDirectory(QStringList filesList) {
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
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "C:/Users/Public", tr("Image Files (*.png *.jpg *.bmp *.txt)"));
}

void MainWindow::on_pushButton_2_clicked()
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

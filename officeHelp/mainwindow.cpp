#include <QFileDialog>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow),
	  mServerManager(new ServerManager),
	  mRequestsHandler(new RequestsHandler(mServerManager)) {
	ui->setupUi(this);

	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(catalogPathChangeSlot(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(wordToSearchChangeSlot(QString)));
	QObject::connect(this, SIGNAL(searchButtonClicked()),
					  mRequestsHandler, SLOT(searchButtonClicked()));
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
	ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pathBox_editingFinished() {
	emit onPathBoxEditingFinishedSignal(ui->pathBox->text());
}

void MainWindow::on_textToFindBox_editingFinished() {
	emit onTextToFindBoxEditingFinishedSignal(ui->textToFindBox->text());
}

void MainWindow::on_radioButton_clicked() {
	emit button1Clicked(CUS::inThisFile);
}

void MainWindow::on_radioButton_2_clicked() {
	emit button1Clicked(CUS::inThisCatalog);
}

void MainWindow::on_radioButton_3_clicked() {
	emit button1Clicked(CUS::inThisCatalogRecursevely);
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

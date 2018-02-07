#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow),
	  mRequestsHandler(new RequestsHandler),
	  mServerManager(new ServerManager) {
	ui->setupUi(this);

	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(catalogPathChangeSlot(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(wordToSearchChangeSlot(QString)));
	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					  mServerManager, SLOT(setPath(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					  mServerManager, SLOT(setTextToSearch(QString)));

	ui->pathBox->setText(mServerManager->getPath());
	ui->textToFindBox->setText(mServerManager->getTextToSearch());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pathBox_editingFinished() {
	if (ui->pathBox->text() != mServerManager->getPath())
		emit onPathBoxEditingFinishedSignal(ui->pathBox->text());
}

void MainWindow::on_textToFindBox_editingFinished() {
	if (ui->textToFindBox->text() != mServerManager->getTextToSearch())
		emit onTextToFindBoxEditingFinishedSignal(ui->textToFindBox->text());
}





//Pomysł -> w trakcie działania programu można ustawiać te bozy na "setreadonly" żeby nie
// było jakiś problemów

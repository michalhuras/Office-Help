#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow),
	  mRequestsHandler(new RequestsHandler),
	  mTextToSearch("ala"), mPath("C:/Users/Public/KatalogTestowy") {
	ui->setupUi(this);

	QObject::connect(this, SIGNAL(onPathBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(catalogPathChangeSlot(QString)));
	QObject::connect(this, SIGNAL(onTextToFindBoxEditingFinishedSignal(QString)),
					  mRequestsHandler, SLOT(wordToSearchChangeSlot(QString)));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pathBox_editingFinished() {
	if (ui->pathBox->text() != mPath)
		emit onPathBoxEditingFinishedSignal(ui->pathBox->text());
}

void MainWindow::on_textToFindBox_editingFinished() {
	if (ui->textToFindBox->text() != mTextToSearch)
		emit onTextToFindBoxEditingFinishedSignal(ui->textToFindBox->text());
}

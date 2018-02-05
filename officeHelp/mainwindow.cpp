#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mRequestsHandler(NULL) {
	ui->setupUi(this);

	path = "C:/Users/Public/KatalogTestowy" ;
	textToSearch = "ala" ;

	mRequestsHandler = new RequestsHandler;

	boost::signal<void ()> onPathBoxEditingFinishedSignal;
	onPathBoxEditingFinishedSignal.connect(mRequestsHandler->setCatalogPath());
	boost::signal<void ()> onTextToFindBoxEditingFinishedSignal;
	onTextToFindBoxEditingFinishedSignal.connect(mRequestsHandler->setWordToSearch());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pathBox_editingFinished() {
	onPathBoxEditingFinishedSignal();
}

void MainWindow::on_textToFindBox_editingFinished() {
	onTextToFindBoxEditingFinishedSignal();
}

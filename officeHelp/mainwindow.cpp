#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	path = "C:/Users/Public/KatalogTestowy" ;
	textToSearch = "ala" ;
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pathBox_editingFinished()
{
	//tu będzie sygnał emitowany
}

void MainWindow::on_textToFindBox_editingFinished()
{
	//tu będzie sygnał emitowany
}

#include "ui_FileDialog.hpp"
#include "ui_ui_FileDialog.h"

FileDialog::FileDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FileDialog)
{
	ui->setupUi(this);
	newPath = "C:/";

	dirModel = new QFileSystemModel(this);
	dirModel->setFilter(QDir::NoDotAndDotDot |
						QDir::AllDirs);
	dirModel->setRootPath(newPath);
	ui->treeView->setModel(dirModel);
	ui->treeView->hideColumn(1);
	ui->treeView->hideColumn(2);
	ui->treeView->hideColumn(3);

	fileModel = new QFileSystemModel(this);
	fileModel->setFilter(
			QDir::NoDotAndDotDot |
			QDir::Files);
	fileModel->setRootPath(newPath);
	ui->listView->setModel(fileModel);
}

FileDialog::~FileDialog()
{
	delete ui;
}

void FileDialog::on_treeView_clicked(const QModelIndex &index)
{
	newPath = dirModel->fileInfo(index).absoluteFilePath();
	newName = "";
	ui->listView->setRootIndex(fileModel->setRootPath(newPath));
}

void FileDialog::on_buttonBox_accepted()
{
	emit newPathaccepted(newPath, newName);
}

void FileDialog::on_buttonBox_rejected()
{}

void FileDialog::on_listView_clicked(const QModelIndex &index)
{
	newName = fileModel->data(index).toString();
}

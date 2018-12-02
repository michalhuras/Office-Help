#include "ui_FileDialog.hpp"
#include "ui_ui_FileDialog.h"

FileDialog::FileDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FileDialog)
{
	ui->setupUi(this);
}

FileDialog::~FileDialog()
{
	delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include "RequestsHandler.h"
#include "AbstractSubject.h".h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow ,public AbstractSubject {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QString path;
	QString textToSearch;
	RequestsHandler *mRequestsHandler;

private slots:
	void on_lineEdit_3_textChanged(const QString &arg1);
	void on_pathBox_editingFinished();
	void on_textToFindBox_editingFinished();
};

#endif // MAINWINDOW_H

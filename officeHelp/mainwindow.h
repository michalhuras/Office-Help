#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include "RequestsHandler.h"
#include "ServerManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	RequestsHandler *mRequestsHandler;
	ServerManager *mServerManager;

signals:
	void onPathBoxEditingFinishedSignal(QString newValue);
	void onTextToFindBoxEditingFinishedSignal(QString newValue);

private slots:
	void on_pathBox_editingFinished();
	void on_textToFindBox_editingFinished();
};

#endif // MAINWINDOW_H

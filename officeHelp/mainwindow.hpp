#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>

#include "datastructevidence.hpp"
#include "RequestsHandler.hpp"
#include "ServerManager.hpp"

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
	ServerManager *mServerManager;
	RequestsHandler *mRequestsHandler;

signals:
	void onPathBoxEditingFinishedSignal(QString newValue);
	void onTextToFindBoxEditingFinishedSignal(QString newValue);
	void button1Clicked(CUS::searchMode chosenMode);
	void button2Clicked(CUS::searchMode chosenMode);
	void button3Clicked(CUS::searchMode chosenMode);
	void searchButtonClicked();

private slots:
	void on_pathBox_editingFinished();
	void on_textToFindBox_editingFinished();
	void on_radioButton_clicked();
	void on_radioButton_2_clicked();
	void on_radioButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H

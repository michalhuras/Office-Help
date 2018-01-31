#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_lineEdit_3_textChanged(const QString &arg1);

	void on_pathBox_editingFinished();

	void on_textToFindBox_editingFinished();

private:
	Ui::MainWindow *ui;
	QString path;
	QString textToSearch;
};

#endif // MAINWINDOW_H

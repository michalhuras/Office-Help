#ifndef UI_FILEDIALOG_HPP
#define UI_FILEDIALOG_HPP

#include <QDialog>
#include <QString>
#include <QFileSystemModel>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
	Q_OBJECT

public:
	explicit FileDialog(QWidget *parent = 0);
	~FileDialog();

signals:
	void newPathaccepted(QString newPath, QString newName);

private slots:
	void on_treeView_clicked(const QModelIndex &index);
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

	void on_listView_clicked(const QModelIndex &index);

private:
	Ui::FileDialog *ui;
	QFileSystemModel *dirModel;
	QFileSystemModel *fileModel;
	QString newPath;
	QString newName;
};

#endif // UI_FILEDIALOG_HPP

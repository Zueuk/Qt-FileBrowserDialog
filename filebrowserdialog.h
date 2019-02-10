#pragma once

#include <QDialog>
#include <QItemSelection>
#include <QFileSystemModel>

namespace Ui {
class FileBrowserDialog;
}

class FileBrowserDialog : public QDialog
{
	Q_OBJECT

	QFileSystemModel* dirModel;
	QFileSystemModel* fileModel;

	QString selectedFilename;

public:
	explicit FileBrowserDialog(QString path, QWidget* parent = nullptr);
	~FileBrowserDialog();

	QString selectedFile() const { return selectedFilename; }

private:
	Ui::FileBrowserDialog *ui;

protected slots:
	void dirItemClicked(const QModelIndex& index);
	void fileItemActivated(const QModelIndex& index);
	void fileSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
};

#include "filebrowserdialog.h"
#include "ui_filebrowserdialog.h"

#include <QScrollBar>

const QSize iconSize(128, 128);

FileBrowserDialog::FileBrowserDialog(QString path, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::FileBrowserDialog)
{
	ui->setupUi(this);

	setWindowFlags(Qt::Window);

	ui->filePathLineEdit->setText(path);

	dirModel = new QFileSystemModel(this);
	dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	dirModel->setRootPath(path);

	ui->dirTreeView->setModel(dirModel);
	ui->dirTreeView->hideColumn(1);
	ui->dirTreeView->hideColumn(2);
	ui->dirTreeView->hideColumn(3);
	ui->dirTreeView->setRootIndex(dirModel->index(path));
	ui->dirTreeView->expandToDepth(3);

	connect(ui->dirTreeView, &QTreeView::clicked, this, &FileBrowserDialog::dirItemClicked);

	fileModel = new QFileSystemModel(this);
	fileModel->setFilter(QDir::Files);
	fileModel->setRootPath(path);

	ui->fileListView->setIconSize(iconSize);
	ui->fileListView->setModel(fileModel);
	ui->fileListView->setRootIndex(fileModel->index(path));

	connect(ui->fileListView, &QListView::activated, this, &FileBrowserDialog::fileItemActivated);
	connect(ui->fileListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FileBrowserDialog::fileSelectionChanged);
}

FileBrowserDialog::~FileBrowserDialog() {
	delete ui;
}

void FileBrowserDialog::dirItemClicked(const QModelIndex &index) {
	Q_ASSERT(index.isValid());

	QString path = dirModel->filePath(index);
	ui->filePathLineEdit->setText(path);

	ui->fileListView->setRootIndex(fileModel->setRootPath(path));
	ui->fileListView->verticalScrollBar()->setValue(0);
}

void FileBrowserDialog::fileItemActivated(const QModelIndex &index) {
	selectedFilename = fileModel->filePath(index);
	accept();
}

void FileBrowserDialog::fileSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
	Q_UNUSED(deselected);

	if (!selected.isEmpty()) {
		QModelIndex index = selected.first().topLeft();
		if (index.isValid()) {
			QFileInfo fi = fileModel->fileInfo(index);
			ui->filenameLineEdit->setText(fi.fileName());
			return;
		}
	}
	ui->filenameLineEdit->clear();
}

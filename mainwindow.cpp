#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filebrowserdialog.h"

#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->actionOpenFile, &QAction::triggered, this, &MainWindow::onOpenFile);
	connect(ui->actionAboutQt, &QAction::triggered, this, &MainWindow::onAboutQt);

	fileDialogPath = QDir::homePath();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onOpenFile()
{
	FileBrowserDialog fd(fileDialogPath, this);
	int result = fd.exec();

	ui->textEdit->append(QString("File dialog result = %1").arg(result));
	if (result != 0) {
		ui->textEdit->append(QString("Selected file name: \"%1\"").arg(fd.selectedFile()));
	}
}

void MainWindow::onAboutQt() {
	QMessageBox::aboutQt(this);
}

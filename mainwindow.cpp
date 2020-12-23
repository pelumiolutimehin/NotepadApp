#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}
//a
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());//a
}

void MainWindow::on_actionOpen_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(fname);
    currentFile = fname;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fname);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);//a
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fname = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(fname);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fname;
     setWindowTitle(fname);
     QTextStream out(&file);
     QString text = ui->textEdit->toPlainText();
     out <<text;//a
     file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    //start
    QPrinter printer, a;
    printer.setPrinterName("Printer Name");//a
    QPrintDialog pDialog(&printer);
    if(pDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }
    ui->textEdit->print(&printer); //a
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy(); //a
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste(); //a
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut(); //A
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();//a
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();//A
}

#include "AutoscopeFtpDialog.hpp"
#include "ui_AutoscopeFtpDialog.h"

#include <QDebug>

AutoscopeFtpDialog::AutoscopeFtpDialog(QWidget *parent) :
    StelDialog ("AutoscopeFtpDialog")
{
    ui = new Ui_AutoscopeFtpDialog();
}

AutoscopeFtpDialog::~AutoscopeFtpDialog()
{
    delete ui;
}

void AutoscopeFtpDialog::createDialogContent()
{
    ui->setupUi(dialog);

    ui->ftpServerEditor->setText("ftp://localhost");
    ui->statusLabel->setText("Please enter the name of an FTP server.");

    progressDialog = new QProgressDialog(dialog);

    //seticon cdtoperantbutton
    ui->cdToParentButton->setIcon(QPixmap(":/Autoscope/leaveFolder.png"));

    connect(ui->fileList, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(processItem(QTreeWidgetItem*,int)));
    connect(ui->fileList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(enableDownloadButton()));
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectOrDisconnect()));
    connect(ui->cdToParentButton, SIGNAL(clicked()), this, SLOT(cdToParent()));
    connect(ui->downloadButton, SIGNAL(clicked()), this, SLOT(downloadFile()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void AutoscopeFtpDialog::retranslate()
{

}

void AutoscopeFtpDialog::connectOrDisconnect()
{
    if (ftp) {
        ftp->abort();
        ftp->deleteLater();
        ftp = 0;

        ui->fileList->setEnabled(false);
        ui->cdToParentButton->setEnabled(false);
        ui->downloadButton->setEnabled(false);
        ui->connectButton->setEnabled(true);
        ui->connectButton->setText(tr("Connect"));
        /*
#ifndef QT_NO_CURSOR
        setCursor(Qt::ArrowCursor);
#endif*/
        ui->statusLabel->setText(tr("Please enter the name of an FTP server."));
        return;
    }
/*
#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif*/

    connectToFtp();
}

void AutoscopeFtpDialog::connectToFtp()
{
    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandFinished(int,bool)),
            this, SLOT(ftpCommandFinished(int,bool)));
    connect(ftp, SIGNAL(listInfo(QUrlInfo)),
            this, SLOT(addToList(QUrlInfo)));
    connect(ftp, SIGNAL(dataTransferProgress(qint64,qint64)),
            this, SLOT(updateDataTransferProgress(qint64,qint64)));

    ui->fileList->clear();
    currentPath.clear();
    isDirectory.clear();

    QUrl url(ui->ftpServerEditor->text());
    if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp")) {
        ftp->connectToHost(ui->ftpServerEditor->text(), 21);
        ftp->login();
    } else {
        ftp->connectToHost(url.host(), url.port(21));

        if (!url.userName().isEmpty())
            ftp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
        else
            ftp->login();
        if (!url.path().isEmpty())
            ftp->cd(url.path());
    }

    ui->fileList->setEnabled(true);
    ui->connectButton->setEnabled(false);
    ui->connectButton->setText(tr("Disconnect"));
    ui->statusLabel->setText(tr("Connecting to FTP server %1...")
                         .arg(ui->ftpServerEditor->text()));
}

void AutoscopeFtpDialog::downloadFile()
{
    QString fileName = ui->fileList->currentItem()->text(0);

    if (QFile::exists(fileName)) {
        QMessageBox::information(dialog, tr("FTP"),
                                 tr("There already exists a file called %1 in "
                                    "the current directory.")
                                 .arg(fileName));
        return;
    }

    file = new QFile(pathToSaveFile+"/"+fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(dialog, tr("FTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        return;
    }

    ftp->get(ui->fileList->currentItem()->text(0), file);

    progressDialog->setLabelText(tr("Downloading %1...").arg(fileName));
    ui->downloadButton->setEnabled(false);
    progressDialog->exec();
}

void AutoscopeFtpDialog::cancelDownload()
{
    ftp->abort();

    if (file->exists()) {
        file->close();
        file->remove();
    }
    delete file;
}

void AutoscopeFtpDialog::ftpCommandFinished(int, bool error)
{
    /*
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif*/

    if (ftp->currentCommand() == QFtp::ConnectToHost) {
        if (error) {
            QMessageBox::information(dialog, tr("FTP"),
                                     tr("Unable to connect to the FTP server "
                                        "at %1. Please check that the host "
                                        "name is correct.")
                                     .arg(ui->ftpServerEditor->text()));
            connectOrDisconnect();
            return;
        }
        ui->statusLabel->setText(tr("Logged onto %1.")
                             .arg(ui->ftpServerEditor->text()));
        ui->fileList->setFocus();
        ui->downloadButton->setDefault(true);
        ui->connectButton->setEnabled(true);
        return;
    }

    if (ftp->currentCommand() == QFtp::Login)
        ftp->list();

    if (ftp->currentCommand() == QFtp::Get) {
        if (error) {
            ui->statusLabel->setText(tr("Canceled download of %1.")
                                 .arg(file->fileName()));
            file->close();
            file->remove();
        } else {
            ui->statusLabel->setText(tr("Downloaded %1 to current directory.")
                                 .arg(file->fileName()));
            file->close();
        }
        delete file;
        enableDownloadButton();
        progressDialog->hide();

    } else if (ftp->currentCommand() == QFtp::List) {
        if (isDirectory.isEmpty()) {
            ui->fileList->addTopLevelItem(new QTreeWidgetItem(QStringList() << tr("<empty>")));
            ui->fileList->setEnabled(false);
        }
    }
}

void AutoscopeFtpDialog::addToList(const QUrlInfo &urlInfo)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, urlInfo.name());
    item->setText(1, QString::number(urlInfo.size()));
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));


    //seticon

    QPixmap pixmap(urlInfo.isDir() ? ":/Autoscope/folder.png" : ":/Autoscope/file.png");
    item->setIcon(0, pixmap);

    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui->fileList->addTopLevelItem(item);
    if (!ui->fileList->currentItem()) {
        ui->fileList->setCurrentItem(ui->fileList->topLevelItem(0));
        ui->fileList->setEnabled(true);
    }
}

void AutoscopeFtpDialog::processItem(QTreeWidgetItem *item, int column)
{
    QString name = item->text(0);
    if (isDirectory.value(name)) {
        ui->fileList->clear();
        isDirectory.clear();
        currentPath += '/';
        currentPath += name;
        ftp->cd(name);
        ftp->list();
        ui->cdToParentButton->setEnabled(true);
        /*
#ifndef QT_NO_CURSOR
        setCursor(Qt::WaitCursor);
#endif*/
        return;
    }
}

void AutoscopeFtpDialog::cdToParent()
{
    /*
#ifndef QT_NO_CURSOR
    setCursor(Qt::WaitCursor);
#endif*/
    ui->fileList->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty()) {
        ui->cdToParentButton->setEnabled(false);
        ftp->cd("/");
    } else {
        ftp->cd(currentPath);
    }
    ftp->list();
}

void AutoscopeFtpDialog::updateDataTransferProgress(qint64 readBytes,
                                           qint64 totalBytes)
{
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(readBytes);
}

void AutoscopeFtpDialog::enableDownloadButton()
{
    QTreeWidgetItem *current = ui->fileList->currentItem();
    if (current) {
        QString currentFile = current->text(0);
        ui->downloadButton->setEnabled(!isDirectory.value(currentFile));
    } else {
        ui->downloadButton->setEnabled(false);
    }
}

void AutoscopeFtpDialog::enableConnectButton()
{
    // Save the used configuration

    ui->connectButton->setEnabled(true);
    ui->statusLabel->setText(tr("Please enter the name of an FTP server."));
}


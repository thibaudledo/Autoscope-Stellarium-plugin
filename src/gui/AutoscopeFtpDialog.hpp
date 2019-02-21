#ifndef AUTOSCOPEFTPDIALOG_HPP
#define AUTOSCOPEFTPDIALOG_HPP

#include "StelDialog.hpp"
#include "ui_AutoscopeFtpDialog.h"

#include <QWidget>
#include <QFtp>
#include <QProgressDialog>
#include <QTreeWidgetItem>
#include <QFile>
#include <QUrl>
#include <QMessageBox>

class AutoscopeFtpDialog : public StelDialog
{
    Q_OBJECT

public:
    explicit AutoscopeFtpDialog(QWidget *parent = nullptr);
    ~AutoscopeFtpDialog();

    void setPathToSaveFile(QString path){pathToSaveFile = path;}

protected:
    void createDialogContent();

private:
    Ui_AutoscopeFtpDialog *ui;

    bool isConnected = false;
    QFtp* ftp = nullptr;

    QFile* file;
    QHash<QString, bool> isDirectory;
    QString currentPath;
    QString pathToSaveFile;

    QProgressDialog* progressDialog;

public slots:
    void retranslate();

private slots:
    void connectOrDisconnect();
    void downloadFile();
    void cancelDownload();
    void connectToFtp();

    void ftpCommandFinished(int commandId, bool error);
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem *item, int column);
    void cdToParent();
    void updateDataTransferProgress(qint64 readBytes,
                                    qint64 totalBytes);
    void enableDownloadButton();
    void enableConnectButton();
};

#endif // AUTOSCOPEFTPDIALOG_HPP

#ifndef LUXURYCOINUPDATEDIALOG_H
#define LUXURYCOINUPDATEDIALOG_H

#include <QDialog>
#include <QTextBrowser>
#include <QGridLayout>
#include <QLabel>

#include "luxurycoinupdater.h"

class LuxuryCoinUpdateDialog : public QDialog
{
    Q_OBJECT

    QLabel* currentVersionTitleLabel;
    QLabel* currentVersionContentLabel;
    QLabel* remoteVesionTitleLabel;
    QLabel* remoteVesionContentLabel;
    QTextBrowser* updateInfoText;
    QGridLayout*  mainLayout;
    QLabel* downloadLinkLabel;

    void setRemoteVersion(const QString& version);
    void setCurrentVersion(const QString& version);
    void setBodyText(const QString& bodyText);
    void setDownloadLink(const QString& link);

public:
    explicit LuxuryCoinUpdateDialog(QWidget *parent = 0);

    void setUpdateRelease(const LuxuryCoinReleaseInfo &rel);

signals:

public slots:
};

#endif // LUXURYCOINUPDATEDIALOG_H

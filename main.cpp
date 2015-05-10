#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include <QUrl>
#include <QDesktopServices>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    QString mapFilename = QString("");
    QString objectType= QString("");
    QString prevValue= QString("");

    foreach (QString value, QCoreApplication::arguments()) {
        if (prevValue.contains(QString("-map"))) {
            mapFilename = value;
        }
        if (prevValue.contains(QString("-type"))) {
            objectType = value;
        }
        prevValue = value;
    }
    QFileInfo fileInfo = QFileInfo(mapFilename);
    QString typePath = fileInfo.canonicalPath() + QString("/../") + QString(objectType);
    if (!QFile::exists (typePath) ) {
        QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).canonicalPath();
        QFile::copy( appPath + "/flare-dialog-template.txt", typePath);
    }
    QString urlPath = "file://" + typePath;
    QDesktopServices::openUrl(urlPath);
    return a.exec();
}

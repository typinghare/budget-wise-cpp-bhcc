#include "FIleUtil.h"

#include <QDebug>
#include <QFileInfo>

bool FileUtil::open(QFile &file, const QIODevice::OpenMode openMode, std::function<void(QFile&)> callback) {
    // Retrieve the aboslute path
    const QString absolutePath = QFileInfo(file).absoluteFilePath();

    // Open the file; return false if failing to open the file
    if (!file.open(openMode)) {
        qDebug() << "Failed to open file:" << absolutePath
                 << "Error:" << file.errorString();
        return false;
    }

    // Invoke the callback function
    callback(file);

    // Close the file
    file.close();

    // Return true representing the success
    return true;
}

bool FileUtil::read(QFile &file, std::function<void(QTextStream&)> callback) {
    return FileUtil::open(file, QIODevice::ReadOnly, [&callback](QFile &file) {
        QTextStream inStream(&file);
        callback(inStream);
    });
}

bool write(QFile &file, std::function<void(QTextStream&)> callback) {
    return FileUtil::open(file, QIODevice::WriteOnly, [&callback](QFile &file) {
        QTextStream inStream(&file);
        callback(inStream);
    });
}

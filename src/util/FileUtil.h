#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QFile>
#include <QIODevice>

/**
 * @brief Collection of utility functions related to file operations.
 */
class FileUtil {
public:
    /**
     * @brief Opens a file; prints the absolute file path to the console; closes the file automatically.
     * @param file The file object to be opened.
     * @param openMode The mode in which to open the file.
     * @param callback The callback function to be invoked after successfully opening the file.
     * @return true if file is opened successfully; false otherwise.
     */
    static bool open(QFile &file, const QIODevice::OpenMode openMode, std::function<void(QFile&)> callback);

    /**
     * @brief Reads a file.
     * @param file The file to read.
     * @param callback The callback function to be invoked after successfully opening the file.
     * @return true if file is opened successfully; false otherwise.
     */
    static bool read(QFile &file, std::function<void(QTextStream&)> callback);

    /**
     * @brief Writes a file.
     * @param file The file to write.
     * @param callback The callback function to be invoked after successfully opening the file.
     * @return true if file is opened successfully; false otherwise.
     */
    static bool write(QFile &file, std::function<void(QTextStream&)> callback);

};

#endif // FILEUTIL_H

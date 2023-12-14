#ifndef PASSWORDUTIL_H
#define PASSWORDUTIL_H

#include <QString>

/**
 * @brief Collection of utility functions related to password processing and security.
 */
class PasswordUtil {
public:
    /**
     * @brief Encrypts a text.
     * @param raw
     * @param secretKey
     * @return
     */
    static QString encrypt(const QString& raw, const QString& secretKey);

    /**
     * @brief Checks if the encrypted text matches the raw text.
     * @param raw
     * @param encrypted
     * @param secretKey
     * @return
     */
    static bool match(const QString& raw, const QString& encrypted, const QString& secretKey);
};

#endif // PASSWORDUTIL_H

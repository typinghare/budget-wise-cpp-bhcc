#ifndef PASSWORDUTIL_H
#define PASSWORDUTIL_H

#include <QString>

/**
 * @brief Collection of utility functions related to password processing and security.
 */
class PasswordUtil {
public:
    static QString encrypt(const QString& raw, const QString& secretKey);

    static bool match(const QString& raw, const QString& encrypted, const QString& secretKey);
};

#endif // PASSWORDUTIL_H

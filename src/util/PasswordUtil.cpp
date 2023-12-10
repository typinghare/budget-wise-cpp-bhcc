#include "PasswordUtil.h"

int getShiftDistance(const QString& secretKey) {
    int shift = 0;
    for (char i: secretKey.toStdString()) {
        shift += i;
    }
    shift %= 26;

    return shift;
}

QString PasswordUtil::encrypt(const QString& raw, const QString& secretKey) {
    const int shiftDistance = getShiftDistance(secretKey);

    std::string encrypted;
    for (char c: raw.toStdString()) {
        unsigned char shiftedChar = c + shiftDistance;
        if (shiftedChar > 125) shiftedChar -= 77;
        encrypted += shiftedChar;
    }

    return QString::fromStdString(encrypted);
}

bool PasswordUtil::match(const QString &raw, const QString &encrypted, const QString &secretKey) {
    const int shiftDistance = getShiftDistance(secretKey);

    std::string original;
    for (char c: encrypted.toStdString()) {
        unsigned char shiftedChar = c - shiftDistance;
        if (shiftedChar < 48) shiftedChar += 77;
        original += shiftedChar;
    }

    return original == raw.toStdString() ;
}

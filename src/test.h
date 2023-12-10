#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QDebug>

#include "utils.h"

void testPasswordUtil() {
    QString raw = "test";
    QString encrypted = PasswordUtil::encrypt(raw, "1234");
    qDebug() << encrypted;
    qDebug() << PasswordUtil::match(raw, encrypted, "1234");
}

#endif // TEST_H

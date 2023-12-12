#include "UserInfoRepository.h"

#include <QSqlQuery>
#include <QSqlError>

UserInfoRepository::UserInfoRepository() {}

UserInfo* UserInfoRepository::create(unsigned int userId) {
    const float balance = 0.0;

    QSqlQuery query;
    query.prepare("INSERT INTO user_info (user_id, balance) VALUES (:userId, :balance)");
    query.bindValue(":userId", userId);
    query.bindValue(":balance", balance);

    if (!query.exec()) {
        qDebug() << "Failed to create user info:" << query.lastError().text();
        return nullptr;
    }

    return new UserInfo(query.lastInsertId().toInt(), userId, balance);
}

float UserInfoRepository::getBalance(unsigned int userId) {
    QSqlQuery query;
    query.prepare("SELECT balance FROM user_info WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        throw new FailToGetUserInfoException();
    }

    return query.value("balance").toFloat();
}

bool UserInfoRepository::updateBalance(unsigned int userId, float balance) {
    QSqlQuery query;
    query.prepare("UPDATE user_info SET balance = :balance WHERE user_id = :userId");
    query.bindValue(":userId", userId);
    query.bindValue(":balance", balance);

    if (!query.exec()) {
        qDebug() << "Failed to update user's balance:" << query.lastError().text();
        return false;
    }

    return true;
}

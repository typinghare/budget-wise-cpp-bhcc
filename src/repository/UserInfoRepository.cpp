#include "UserInfoRepository.h"

#include <QSqlQuery>
#include <QSqlError>

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

UserInfo* UserInfoRepository::getByUserId(unsigned int userId) {
    QSqlQuery query;
    query.prepare("SELECT id, balance FROM user_info WHERE user_id = :userId LIMIT 1");
    query.bindValue(":userId", userId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Fail to get user by user ID";
        return nullptr;
    }

    unsigned int id = query.value("id").toInt();
    float balance = query.value("balance").toFloat();

    return new UserInfo(id, userId, balance);
}

bool UserInfoRepository::updateBalance(unsigned int userId, float balance) {
    qDebug() << balance;
    QSqlQuery query;
    query.prepare("UPDATE user_info SET balance = :balance WHERE user_id = :userId");
    query.bindValue(":balance", balance);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to update user's balance:" << query.lastError().text();
        return false;
    }

    return true;
}

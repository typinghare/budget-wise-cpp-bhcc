#include "UserRepository.h"

#include <QSqlQuery>
#include <QSqlError>

User* UserRepository::get(unsigned int id) {
    QSqlQuery query;
    query.prepare("SELECT username, auth_string, email FROM user WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        return nullptr;
    }

    QString username = query.value("username").toString();
    QString authString = query.value("auth_string").toString();
    QString email = query.value("email").toString();

    return new User(id, username, authString, email);
}

User* UserRepository::getByUsername(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT id, username, auth_string, email FROM user WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec() || !query.next()) {
        return nullptr;
    }

    unsigned int id = query.value("id").toInt();
    QString authString = query.value("auth_string").toString();
    QString email = query.value("email").toString();

    return new User(id, username, authString, email);
}

User* UserRepository::create(const QString& username, const QString& authString, const QString& email) {
    QSqlQuery query;
    query.prepare("INSERT INTO user (username, auth_string, email) VALUES (:username, :authString, :email)");

    query.bindValue(":username", username);
    query.bindValue(":authString", authString);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Failed to create user:" << query.lastError().text();
        return nullptr;
    }

    // Retrieve the auto-generated user ID
    unsigned int id = query.lastInsertId().toInt();

    return new User(id, username, authString, email);
}

bool UserRepository::updateAuthString(unsigned int id, const QString& authString) {
    QSqlQuery query;
    query.prepare("UPDATE user SET auth_string = :authString WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":authString", authString);

    if (!query.exec()) {
        qDebug() << "Failed to update user's authentication string: " << query.lastError().text();
        return false;
    }

    return true;
}

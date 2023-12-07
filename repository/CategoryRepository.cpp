#include "CategoryRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CategoryRepository::CategoryRepository() = default;

Category* CategoryRepository::getCategory(unsigned int id) {
    QSqlQuery query;
    query.prepare("SELECT user_id, name FROM category WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get category:" << query.lastError().text();
    }

    if (!query.next()) {
        return nullptr;
    }

    unsigned int userId = query.value("user_id").toInt();
    QString name = query.value("name").toString();

    return new Category(id, userId, name);
}

Category* CategoryRepository::createCategory(unsigned int userId, const QString &name) {
    QSqlQuery query;
    query.prepare("INSERT INTO category (user_id, name) VALUES (:userId, :name)");

    query.bindValue(":userId", userId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to create category:" << query.lastError().text();
        return nullptr;
    }

    // Retrieve the auto-generated user ID
    unsigned int id = query.lastInsertId().toInt();

    return new Category(id, userId, name);
}

Category* CategoryRepository::getByUserIdAndName(unsigned int userId, const QString& name) {
    QSqlQuery query;
    query.prepare("SELECT id FROM category WHERE user_id = :userId AND name = :name LIMIT 1");
    query.bindValue(":userId", userId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to get category:" << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    unsigned int id = query.value("id").toInt();

    return new Category(id, userId, name);
}

QList<Category *> CategoryRepository::getAll(unsigned int userId) {
    QList<Category *> list;

    QSqlQuery query;
    query.prepare("SELECT id, user_id, name FROM category WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to get categories:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int userId = query.value("user_id").toInt();
        QString name = query.value("name").toString();
        list << new Category(id, userId, name);
    }

    return list;
}

bool CategoryRepository::remove(unsigned int userId, const QString& name) {
    return true;
}

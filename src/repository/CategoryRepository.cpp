#include "CategoryRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CategoryRepository::CategoryRepository() = default;

Category* CategoryRepository::get(unsigned int id) {
    QSqlQuery query;
    query.prepare("SELECT user_id, name FROM category WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get category:" << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    unsigned int userId = query.value("user_id").toInt();
    QString name = query.value("name").toString();

    return new Category(id, userId, name);
}

Category* CategoryRepository::create(unsigned int userId, const QString &name) {
    QSqlQuery query;
    query.prepare("INSERT INTO category (user_id, name) VALUES (:userId, :name)");

    query.bindValue(":userId", userId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to create category:" << query.lastError().text();
        return nullptr;
    }

    return new Category(query.lastInsertId().toInt(), userId, name);
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

    return new Category(query.value("id").toInt(), userId, name);
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
        QString name = query.value("name").toString();
        list << new Category(id, userId, name);
    }

    return list;
}

bool CategoryRepository::remove(unsigned int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM category WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to delete category:" << query.lastError().text();
        return false;
    }

    return true;
}

bool CategoryRepository::update(unsigned int id, const QString& newName) {
    QSqlQuery query;
    query.prepare("UPDATE category SET name = :newName WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":newName", newName);

    if (!query.exec()) {
        qDebug() << "Failed to update category:" << query.lastError().text();
        return false;
    }

    return true;
}

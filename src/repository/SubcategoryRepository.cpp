#include "SubcategoryRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Subcategory* SubcategoryRepository::get(unsigned int id) {
    QSqlQuery query;
    query.prepare("SELECT user_id, category_id, name FROM subcategory WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get category:" << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    unsigned int userId = query.value("user_id").toInt();
    unsigned int categoryId = query.value("category_id").toInt();
    QString name = query.value("name").toString();

    return new Subcategory(id, userId, categoryId, name);
}

Subcategory* SubcategoryRepository::create(
    unsigned int userId,
    unsigned int cateogryId,
    const QString& name) {
    QSqlQuery query;
    QString sql = "INSERT INTO subcategory "
                  "(user_id, category_id, name) VALUES "
                  "(:userId, :categoryId, :name)";
    query.prepare(sql);
    query.bindValue(":userId", userId);
    query.bindValue(":categoryId", cateogryId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to create subcategory:" << query.lastError().text();
        return nullptr;
    }

    return new Subcategory(query.lastInsertId().toInt(), userId, cateogryId, name);
}

QList<Subcategory*> SubcategoryRepository::getAllByUserId(unsigned int userId) {
    QList<Subcategory*> list;

    QSqlQuery query;
    query.prepare("SELECT id, category_id, name FROM subcategory WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to get subcategories:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int categoryId = query.value("category_id").toInt();
        QString name = query.value("name").toString();
        list << new Subcategory(id, userId, categoryId, name);
    }

    return list;
}

QList<Subcategory*> SubcategoryRepository::getAllByCategoryId(unsigned int categoryId) {
    QList<Subcategory*> list;

    QSqlQuery query;
    query.prepare("SELECT * FROM subcategory WHERE category_id = :categoryId");
    query.bindValue(":categoryId", categoryId);

    if (!query.exec()) {
        qDebug() << "Failed to get subcategories:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int userId = query.value("user_id").toInt();
        unsigned int categoryId = query.value("category_id").toInt();
        QString name = query.value("name").toString();
        list << new Subcategory(id, userId, categoryId, name);
    }

    return list;
}

Subcategory* SubcategoryRepository::getByUserIdAndCategoryIdAndName(
    unsigned int userId,
    unsigned int categoryId,
    const QString &name) {
    QSqlQuery query;
    QString sql = "SELECT id FROM subcategory "
                  "WHERE user_id = :userId AND category_id = :categoryId AND name = :name LIMIT 1";
    query.prepare(sql);
    query.bindValue(":userId", userId);
    query.bindValue(":categoryId", categoryId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to get the subcategory:" << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    return new Subcategory(query.value("id").toInt(), userId, categoryId, name);
}

bool SubcategoryRepository::removeByCategoryId(unsigned int categoryId) {
    QSqlQuery query;
    query.prepare("DELETE FROM subcategory WHERE category_id = :categoryId");
    query.bindValue(":categoryId", categoryId);

    if (!query.exec()) {
        qDebug() << "Failed to delete subcategories:" << query.lastError().text();
        return false;
    }

    return true;
}

bool SubcategoryRepository::remove(unsigned int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM subcategory WHERE id = :id");
    query.bindValue(":id", id);


    if (!query.exec()) {
        qDebug() << "Failed to delete the subcategory:" << query.lastError().text();
        return false;
    }

    return true;
}

bool SubcategoryRepository::update(unsigned int id, unsigned int categoryId, const QString &name) {
    QSqlQuery query;
    query.prepare("UPDATE subcategory SET category_id = :categoryId, name = :name WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":categoryId", categoryId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to update subcategory:" << query.lastError().text();
        return false;
    }

    return true;
}

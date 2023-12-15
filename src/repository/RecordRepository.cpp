#include "RecordRepository.h"

#include <QSqlQuery>
#include <QSqlError>

Record* RecordRepository::get(unsigned int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM record WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get the record:" << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    unsigned int userId = query.value("user_id").toInt();
    unsigned int categoryId = query.value("category_id").toInt();
    unsigned int subcategoryId = query.value("subcategory_id").toInt();
    QDateTime createdAt = query.value("created_at").toDateTime();
    double amount = query.value("amount").toDouble();

    return new Record(id, userId, categoryId, subcategoryId, createdAt, amount, 0.0);
}

QList<Record*> RecordRepository::getAllByUser(unsigned int userId, bool desc) {
    QList<Record*> list;

    QSqlQuery query;
    QString orderClause(desc ? " ORDER BY id DESC" : "");
    query.prepare("SELECT * FROM record_with_balance WHERE user_id = :userId" + orderClause);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to get records:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int categoryId = query.value("category_id").toInt();
        unsigned int subcategoryId = query.value("subcategory_id").toInt();
        QDateTime createdAt = query.value("created_at").toDateTime();
        double amount = query.value("amount").toDouble();
        double balance = query.value("balance").toDouble();

        list << new Record(id, userId, categoryId, subcategoryId, createdAt, amount, balance);
    }

    return list;
}

QList<Record*> RecordRepository::getAllByCategory(unsigned int categoryId, bool desc) {
    QList<Record*> list;

    QSqlQuery query;
    QString orderClause(desc ? " ORDER BY id DESC" : "");
    query.prepare("SELECT * FROM record_with_balance WHERE category_id = :categoryId"
                          + orderClause);
    query.bindValue(":categoryId", categoryId);

    if (!query.exec()) {
        qDebug() << "Failed to get records:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int userId = query.value("user_id").toInt();
        unsigned int subcategoryId = query.value("subcategory_id").toInt();
        QDateTime createdAt = query.value("created_at").toDateTime();
        double amount = query.value("amount").toDouble();
        double balance = query.value("balance").toDouble();

        list << new Record(id, userId, categoryId, subcategoryId, createdAt, amount, balance);
    }

    return list;
}

QList<Record*> RecordRepository::getAllBySubcategory(unsigned int subcategoryId, bool desc) {
    QList<Record*> list;

    QSqlQuery query;
    QString orderClause(desc ? " ORDER BY id DESC" : "");
    query.prepare("SELECT * FROM record_with_balance WHERE subcategory_id = :subcategoryId"
                  + orderClause);
    query.bindValue(":subcategoryId", subcategoryId);

    if (!query.exec()) {
        qDebug() << "Failed to get records:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int userId = query.value("user_id").toInt();
        unsigned int categoryId = query.value("category_id").toInt();
        QDateTime createdAt = query.value("created_at").toDateTime();
        double amount = query.value("amount").toDouble();
        double balance = query.value("balance").toDouble();

        list << new Record(id, userId, categoryId, subcategoryId, createdAt, amount, balance);
    }

    return list;
}

Record* RecordRepository::create(
    unsigned int userId,
    unsigned int categoryId,
    unsigned int subcategoryId,
    QDateTime createdAt,
    double amount) {

    QSqlQuery query;
    query.prepare("INSERT INTO record "
                  "(user_id, category_id, subcategory_id, created_at, amount) "
                  "VALUES (:userId, :categoryId, :subcategoryId, :createdAt, :amount)");
    query.bindValue(":userId", userId);
    query.bindValue(":categoryId", categoryId);
    query.bindValue(":subcategoryId", subcategoryId);
    query.bindValue(":createdAt", createdAt);
    query.bindValue(":amount", amount);

    if (!query.exec()) {
        qWarning() << "Failed to create a record:" << query.lastError().text();
        return nullptr;
    }

    int recordId = query.lastInsertId().toInt();

    return getWithBalance(recordId);
}

Record* RecordRepository::getWithBalance(unsigned int id) {
    Record* record = get(id);
    if (record == nullptr) {
        return nullptr;
    }

    QSqlQuery query;
    query.prepare("SELECT SUM(amount) AS balance FROM record WHERE id <= :id AND user_id = :userId");
    query.bindValue(":id", record->getId());
    query.bindValue(":userId", record->getUserId());

    if (!query.exec() || !query.next()) {
        delete record;
        return nullptr;
    }

    record->setBalance(query.value("balance").toDouble());
    return record;
}

unsigned int RecordRepository::getLastId(unsigned int userId) {
    QSqlQuery query;
    query.prepare("SELECT id FROM record WHERE user_id = :userId ORDER BY id DESC LIMIT 1");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to get the last record:" << query.lastError().text();
        return 0;
    }

    if (!query.next()) {
        return 0;
    }

    return query.value("id").toInt();
}

bool RecordRepository::remove(unsigned int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM record WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to delete record:" << query.lastError().text();
        return false;
    }

    return true;
}

bool RecordRepository::removeByCategoryId(unsigned int categoryId) {
    QSqlQuery query;
    query.prepare("DELETE FROM record WHERE category_id = :categoryId");
    query.bindValue(":categoryId", categoryId);

    if (!query.exec()) {
        qDebug() << "Failed to delete records of a category:" << query.lastError().text();
        return false;
    }

    return true;
}

bool RecordRepository::removeBySubcategoryId(unsigned int subcategoryId) {
    QSqlQuery query;
    query.prepare("DELETE FROM record WHERE subcategory_id = :subcategoryId");
    query.bindValue(":subcategoryId", subcategoryId);

    if (!query.exec()) {
        qDebug() << "Failed to delete records of a subcategory:" << query.lastError().text();
        return false;
    }

    return true;
}

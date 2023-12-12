#include "RecordRepository.h"

#include <QSqlQuery>
#include <QSqlError>

RecordRepository::RecordRepository() {

}

QList<Record*> RecordRepository::getAll(unsigned int userId) {
    QList<Record*> list;

    QSqlQuery query;
    query.prepare("SELECT id FROM record WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to get records:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        unsigned int id = query.value("id").toInt();
        unsigned int subcategoryId = query.value("subcategory_id").toInt();
        QDateTime createdAt = query.value("created_at").toDateTime();
        double amount = query.value("amount").toDouble();
        double balance = query.value("balance").toDouble();

        list << new Record(id, userId, subcategoryId, createdAt, amount, balance);
    }

    return list;
}

Record* RecordRepository::create(
    unsigned int userId,
    unsigned int subcategoryId,
    QDateTime createdAt,
    double amount,
    double balance) {

    QSqlQuery query;
    query.prepare("INSERT INTO record "
                  "(user_id, subcategory_id, created_at, amount, balance) "
                  "VALUES (:userId, :subcategoryId, :createdAt, :amount, :balance)");
    query.bindValue(":userId", userId);
    query.bindValue(":subcategoryId", subcategoryId);
    query.bindValue(":createdAt", createdAt);
    query.bindValue(":amount", amount);
    query.bindValue(":balance", balance);

    if (!query.exec()) {
        qWarning() << "Failed to create a record:" << query.lastError().text();
        return nullptr;
    }

    int recordId = query.lastInsertId().toInt();

    return new Record(recordId, userId, subcategoryId, createdAt, amount, balance);
}

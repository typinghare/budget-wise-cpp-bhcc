#include "RecordService.h"

#include <QDateTime>

#include "src/Database.h"

RecordService::RecordService() {
}

QList<Record*> RecordService::getAllRecords(unsigned int userId, bool desc) {
    auto recordRepository = Database::getInstance()->getRecordRepository();
    return recordRepository.getAllByUser(userId, desc);
}

QSharedPointer<Record> RecordService::createRecord(
    unsigned int userId,
    unsigned int categoryId,
    unsigned int subcategoryId,
    float amount) {
    auto recordRepository = Database::getInstance()->getRecordRepository();
    auto createdAt = QDateTime::currentDateTime();
    QSharedPointer<Record> record(recordRepository.create(userId, categoryId, subcategoryId, createdAt, amount));
    if (record.isNull()) {
        return record;
    }

    return record;
}

bool RecordService::deleteLastRecord(unsigned int userId) {
    // Get the user's last record
    auto recordRepository = Database::getInstance()->getRecordRepository();
    unsigned int lastRecordId = recordRepository.getLastId(userId);
    if (lastRecordId == 0 ) {
        return false;
    }

    recordRepository.remove(lastRecordId);

    return true;
}
